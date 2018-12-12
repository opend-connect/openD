// =============================================================================
/*!
 * @file       src/interfaces.cpp
 *
 * This file contains the implementation of the interfaces common code.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 ULE Alliance
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 *
 * Initial development by Bithium S.A. [http://www.bithium.com]
 */
// =============================================================================

#include "hanfun/common.h"
#include "hanfun/interface.h"

// =============================================================================
// API
// =============================================================================

using namespace HF;
using namespace HF::Protocol;
using namespace HF::Interfaces;

// =============================================================================
// Helper Functions
// =============================================================================

// =============================================================================
// update_attribute
// =============================================================================
/*!
 * Update the attribute with the given @c uid at given interface.
 *
 * @param [in] itf      pointer to the interface to update the attribute at.
 * @param [in] uid      the UID of the attribute to update.
 * @param [in] payload  the Common::ByteArray containing the value to update the attribute.
 * @param [in] offset   the offset to read the payload from.
 * @param [in] nop      if @c true, do everything except change the attribute value.
 *
 * @retval Common::Result::OK            if the attribute was updated;
 * @retval Common::Result::FAIL_SUPPORT  if the attribute does not exist;
 * @retval Common::Result::FAIL_RO_ATTR  if the attribute does not exist;
 * @retval Common::Result::FAIL_UNKNOWN  otherwise.
 */
// =============================================================================
static Common::Result update_attribute (Interface &itf, uint8_t uid, Common::ByteArray &payload,
                                        uint16_t &offset, bool nop = false)
{
   Common::Result result            = Common::Result::FAIL_UNKNOWN;

   HF::Attributes::IAttribute *attr = itf.attribute (uid);

   if (attr == nullptr)
   {
      result = Common::Result::FAIL_SUPPORT;
   }
   else if (attr->isWritable ())
   {
      if (payload.available (offset, attr->size ()))
      {
         if (!nop)
         {
            offset += attr->unpack (payload, offset);
         }

         result = Common::Result::OK;
      }
      else
      {
         result = Common::Result::FAIL_UNKNOWN;
      }
   }
   else
   {
      offset += attr->size ();

      result  = Common::Result::FAIL_RO_ATTR;
   }

   delete attr;

   return result;
}

// =============================================================================
// update_attributes
// =============================================================================
/*!
 * Update the given interface (@c itf) attributes with the values present in the
 * Common::ByteArray @c payload.
 *
 * @param [in]    itf        the interface instance to update the attributes on.
 * @param [in]    payload    the Common::ByteArray containing the new values for the attributes.
 * @param [inout] offset     the offset at the Common::ByteArray to start reading the values from.
 * @param [in]    resp       boolean indicating if a response is necessary.
 * @param [in]    nop        if @c true, do everything except change the attribute value.
 *
 * @return  pointer to a SetAttributePack::Response instance if a response
 *          is necessary, @c nullptr otherwise.
 */
// =============================================================================
static SetAttributePack::Response *update_attributes (Interface &itf, Common::ByteArray &payload,
                                                      uint16_t &offset, bool resp, bool nop = false)
{
   SetAttributePack::Request request;

   offset += request.unpack (payload, offset);

   SetAttributePack::Response *result = (resp ? new SetAttributePack::Response () : nullptr);

   for (uint8_t i = 0; i < request.count; i++)
   {
      SetAttributePack::Response::Result attr_res;

      offset       += payload.read (offset, attr_res.uid);

      attr_res.code = update_attribute (itf, attr_res.uid, payload, offset, nop);

      if (resp)
      {
         result->results.push_back (attr_res);
      }

      if (attr_res.code == Common::Result::FAIL_SUPPORT ||
          attr_res.code == Common::Result::FAIL_UNKNOWN)
      {
         break;
      }
   }

   return result;
}

// =============================================================================
// update_attributes_atomic
// =============================================================================
/*!
 * Update the given interface (@c itf) attributes with the values present in the
 * Common::ByteArray @c payload, if all values can be set.
 *
 * @param [in]    itf        the interface instance to update the attributes on.
 * @param [in]    payload    the Common::ByteArray containing the new values for the attributes.
 * @param [inout] offset     the offset at the Common::ByteArray to start reading the values from.
 * @param [in]    resp       boolean indicating if a response is necessary.
 *
 * @return  pointer to a HF::Response instance if a response is necessary, @c nullptr otherwise.
 */
// =============================================================================
static Response *update_attributes_atomic (Interface &itf, Common::ByteArray &payload,
                                           uint16_t &offset, bool resp)
{
   uint16_t start                       = offset;

   SetAttributePack::Response *attr_res = update_attributes (itf, payload, offset, true, true);

   Common::Result result                = Common::Result::OK;

   for (auto it = attr_res->results.begin (); it != attr_res->results.end (); ++it)
   {
      result = it->code;

      if (result != Common::Result::OK)
      {
         break;
      }
   }

   delete attr_res;

   if (result == Common::Result::OK)
   {
      offset = start;
      update_attributes (itf, payload, offset, false);
   }

   if (resp)
   {
      return new Response (result);
   }
   else
   {
      return nullptr;
   }
}

// =============================================================================
// AbstractInterface API.
// =============================================================================

// =============================================================================
// AbstractInterface::handle
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractInterface::handle (Packet &packet, Common::ByteArray &payload, uint16_t offset)
{
   Common::Result result = check (packet.message, payload, offset);

   if (result != Common::Result::OK)
   {
      return result;
   }

   result = check_payload_size (packet.message, payload, offset);

   if (result != Common::Result::OK)
   {
      return result;
   }

   if (packet.message.type >= Message::COMMAND_REQ && packet.message.type <= Message::COMMAND_RES)
   {
      return handle_command (packet, payload, offset);
   }
   else if (packet.message.type >= Message::GET_ATTR_REQ &&
            packet.message.type <= Message::ATOMIC_SET_ATTR_PACK_RES)
   {
      return handle_attribute (packet, payload, offset);
   }

   return Common::Result::FAIL_UNKNOWN;
}

// =============================================================================
// AbstractInterface::check_message
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractInterface::check (Message &message, Common::ByteArray &payload, uint16_t offset)
{
   UNUSED (payload);
   UNUSED (offset);

   if (!check_uid (message.itf.id))
   {
      return Common::Result::FAIL_ARG;
   }

   switch (message.type)
   {
      case Message::COMMAND_REQ:
      case Message::COMMAND_RESP_REQ:
      case Message::GET_ATTR_REQ:
      case Message::SET_ATTR_REQ:
      case Message::SET_ATTR_RESP_REQ:
      case Message::SET_ATTR_PACK_REQ:
      case Message::SET_ATTR_PACK_RESP_REQ:
      {
         if (role () != message.itf.role)
         {
            return Common::Result::FAIL_SUPPORT;
         }

         break;
      }
      case Message::COMMAND_RES:
      {
         if (role () == message.itf.role)
         {
            return Common::Result::FAIL_SUPPORT;
         }

         break;
      }
      default:
         break;
   }

   return Common::Result::OK;
}

// =============================================================================
// AbstractInterface::check_payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractInterface::check_payload_size (Message &message, Common::ByteArray &payload,
                                                      uint16_t offset)
{
   uint16_t _payload_size = payload_size (message);

   if (_payload_size != 0)
   {
      if (message.length < _payload_size || payload.size () < offset ||
          (payload.size () - offset) < _payload_size)
      {
         return Common::Result::FAIL_ARG;
      }
   }

   return Common::Result::OK;
}

// =============================================================================
// AbstractInterface::payload_size
// =============================================================================
/*!
 *
 */
// =============================================================================
uint16_t AbstractInterface::payload_size (Message &message) const
{
   return payload_size (message.itf);
}

// =============================================================================
// AbstractInterface::handle_command
// =============================================================================
/*!
 *
 */
// =============================================================================
Common::Result AbstractInterface::handle_command (Packet &packet, Common::ByteArray &payload,
                                                  uint16_t offset)
{
   UNUSED (packet);
   UNUSED (payload);
   UNUSED (offset);

   return Common::Result::FAIL_UNKNOWN;
}

// =============================================================================
// AbstractInterface::handle_attributes
// =============================================================================
/*!
 *
 *
 */
// =============================================================================
Common::Result AbstractInterface::handle_attribute (Packet &packet, Common::ByteArray &payload,
                                                    uint16_t offset)
{
   Common::Result result = Common::Result::OK;

   switch (packet.message.type)
   {
      case Message::GET_ATTR_REQ:
      {
         auto *attr_res = new HF::Attributes::Response (attribute (packet.message.itf.member));
         attr_res->code = (attr_res->attribute != nullptr ? Common::Result::OK :
                           Common::Result::FAIL_SUPPORT);

         Message response (packet.message, attr_res->size ());

         attr_res->pack (response.payload);

         send (packet.source, response);

         delete attr_res;

         break;
      }
      case Message::GET_ATTR_RES:
      {
         // Do nothing.
         break;
      }
      case Message::SET_ATTR_REQ:
      {
         result = update_attribute (*this, packet.message.itf.member, payload, offset);
         break;
      }
      case Message::SET_ATTR_RESP_REQ:
      {
         Common::Result result = update_attribute (*this, packet.message.itf.member, payload, offset);
         Response resp (result);

         Message  response (packet.message, resp.size ());
         resp.pack (response.payload);

         send (packet.source, response);

         break;
      }
      case Message::GET_ATTR_PACK_REQ:
      {
         GetAttributePack::Request request;

         HF::Attributes::UIDS attributes;

         if (packet.message.itf.member == HF::Attributes::Pack::DYNAMIC)
         {
            offset    += request.unpack (payload, offset);
            attributes = request.attributes;
         }
         else
         {
            attributes = this->attributes (packet.message.itf.member);
         }

         GetAttributePack::Response *attr_response = new GetAttributePack::Response ();

         if (result == Common::Result::OK)
         {
            /* *INDENT-OFF* */
            for_each (attributes.begin (), attributes.end (),
                       [attr_response, &result, this](uint8_t uid)
            {
               HF::Attributes::IAttribute *attr = attribute (uid);
               if (attr != nullptr)
               {
                  attr_response->attributes.push_back (attr);
               }
               else
               {
                  result = Common::Result::FAIL_SUPPORT;
               }
            });
            /* *INDENT-ON* */
         }

         attr_response->code = result;

         Message response (packet.message, attr_response->size ());

         attr_response->pack (response.payload);

         send (packet.source, response);

         delete attr_response;

         break;
      }
      case Message::GET_ATTR_PACK_RES:
      {
         // Do nothing.
         break;
      }
      case Message::SET_ATTR_PACK_REQ:
      {
         update_attributes (*this, payload, offset, false);
         break;
      }
      case Message::SET_ATTR_PACK_RESP_REQ:
      {
         SetAttributePack::Response *attr_response = update_attributes (*this, payload, offset, true);

         Message response (packet.message, attr_response->size ());

         attr_response->pack (response.payload);

         send (packet.source, response);

         delete attr_response;

         break;
      }
      case Message::SET_ATTR_PACK_RES:
      {
         // Do nothing.
         break;
      }
      case Message::ATOMIC_SET_ATTR_PACK_REQ:
      {
         update_attributes_atomic (*this, payload, offset, false);
         break;
      }
      case Message::ATOMIC_SET_ATTR_PACK_RESP_REQ:
      {
         Protocol::Response *resp = update_attributes_atomic (*this, payload, offset, true);

         Message response (packet.message, resp->size ());

         resp->pack (response.payload);

         send (packet.source, response);

         delete resp;

         break;
      }
      case Message::ATOMIC_SET_ATTR_PACK_RES:
      {
         // Do nothing.
         break;
      }
      default:
         break;
   }

   return result;
}
