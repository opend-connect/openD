// =============================================================================
/*!
 * @file       inc/hanfun/transport.h
 *
 * This file contains the definition of the transport layer API for the HAN-FUN
 * common implementation.
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
#ifndef HF_TRANSPORT_H
#define HF_TRANSPORT_H

#include "hanfun/common.h"
#include "hanfun/uids.h"
#include "hanfun/protocol.h"

namespace HF
{
   /*!
    * This is the top-level namespace for the transport layer API.
    */
   namespace Transport
   {
      // Forward declaration.
      struct Layer;
      /*!
       * @addtogroup transport Transport Layer API
       * @ingroup devices
       *
       * This module contains the classes that define and implement the common functionality
       * of the %Transport API.
       *
       * This API is used by HAN-FUN devices in an application to send/receive packets in an
       * independent way from the actual transport mechanism being used.
       * @{
       */

      /*!
       * This interface represents a link on the transport layer, used to send data
       * to the remote end-point.
       */
      struct Link
      {
         virtual ~Link() {}

         /*!
          * Get the address of the device this link corresponds to.
          *
          * @return  the address of the device for this link.
          */
         virtual uint16_t address () const = 0;

         /*!
          * Set the address of this link corresponds to.
          *
          * @param [in] addr  the address value to set.
          */
         virtual void address (uint16_t addr) = 0;

         /*!
          * Send the data in the given @c ByteArray using the link to the remote end-point.
          *
          * @param [in] array   reference to the ByteArray containing the data to send.
          */
         virtual void send (Common::ByteArray &array) = 0;

         /*!
          * Return the end-point UID associated with this link.
          *
          * For example, for a ULE transport layer this would return the
          * RFPI/IPUI of the remote device.
          *
          * @return  the UID of the remote device of this link.
          */
         virtual const HF::UID::UID uid () const = 0;
      };

      /*!
       * This is the interface used by the transport layer to signal events comming in from
       * the network.
       */
      struct Endpoint
      {
         // ======================================================================
         // Events
         // ======================================================================
         //! @name Events
         //! @{

         /*!
          * Callback to report that a new transport @c link was been created to a
          * remote device.
          *
          * This link can then be used by the local end-point to send messages to
          * the remote end-point.
          *
          * @param [in] link    pointer to the created link.
          */
         virtual void connected (Link *link) = 0;

         /*!
          * Callback to the report that the given transport @c link no longer is
          * valid and MUST not be used to send messages to the corresponding end-point.
          *
          * At the time of this method call the link MUST not be used to send any
          * further messages to the remote end-point.
          *
          * @param [in] link    pointer to the link disconnected.
          */
         virtual void disconnected (Link *link) = 0;

         /*!
          * Callback to deliver a packet received from the transport layer.
          *
          * @param [in] packet   reference to the received packet.
          * @param [in] payload  reference a ByteArray containing the received data.
          * @param [in] offset   offset from where the received data starts on the @c payload
          *                      byte array buffer.
          */
         virtual void receive (Protocol::Packet &packet, Common::ByteArray &payload,
                               uint16_t offset) = 0;

         //! @}
         // ======================================================================
      };

      /*!
       * This class defines the API for the transport layer.
       */
      struct Layer
      {
         // ======================================================================
         // Commands
         // ======================================================================
         //! @name Commands
         //! @{

         /*!
          * Initialize the associated transport layer.
          *
          * This method should initialize the transport layer using it's default values.
          */
         virtual void initialize () = 0;

         /*!
          * Register the given @c Endpoint to receive events.
          *
          * This should be possible to register multiple end-points, to the transport
          * layer.
          *
          * @param [in] ep    pointer to the end-point to register in the transport layer.
          */
         virtual void add (Endpoint *ep) = 0;

         /*!
          * Free the system resources associated with the given @c Endpoint,
          * and remove it from receiving any further events.
          *
          * If @c ep is @c  nullptr then all end-points should be removed.
          *
          * When all end-points are removed all remaining system resources,
          * associated with this transport layer should be freed.
          *
          * @param ep   pointer to the endpoint to remove from the transport layer.
          */
         virtual void remove (Endpoint *ep = nullptr) = 0;

         /*!
          * Free the system resources associated with this transport layer.
          */
         virtual void destroy () = 0;

         /*!
          * Return the UID of the local device on this transport layer.
          *
          * For example on an ULE device this would return the IPUI of the device.
          *
          * @return  the UID of the local device on this transport layer.
          */
         virtual const HF::UID::UID uid () const = 0;

         //! @}
         // ======================================================================
      };

      /*!
       * Parent class for all HF::Transport::Link implementations.
       */
      class AbstractLink:public Link
      {
         protected:

         //! UID associated with this link.
         HF::UID::UID_T *_uid;

         //! HAN-FUN address associated with the remote end-point.
         uint16_t _address;

         public:

         AbstractLink(UID::UID_T *__uid = nullptr,
                      uint16_t _address = Protocol::BROADCAST_ADDR):
            _uid (__uid), _address (_address)
         {}

         virtual ~AbstractLink() {}

         uint16_t address () const
         {
            return _address;
         }

         void address (uint16_t addr)
         {
            _address = addr;
         }

         const HF::UID::UID uid () const
         {
            return HF::UID::UID(_uid);
         }

         void uid (HF::UID::UID_T *_uid)
         {
            this->_uid = _uid;
         }
      };

      /*!
       * Parent class for all HF::Transport::Layer implementations.
       */
      class AbstractLayer:public Layer
      {
         protected:

         //! List of registered end-points for this layer.
         Common::SimpleList <HF::Transport::Endpoint *> endpoints;

         //! UID associated with the local transport layer.
         HF::UID::UID_T *_uid;

         public:

         AbstractLayer(UID::UID_T *__uid = nullptr):_uid (__uid)
         {}

         virtual ~AbstractLayer()
         {
            delete _uid;
         }

         void initialize () {}

         void destroy () {}

         /*!
          * Add an entry to the list of end-points connected to the transport layer.
          *
          * @param [in] ep pointer to the end-point to add.
          */
         void add (HF::Transport::Endpoint *ep)
         {
            assert (ep != nullptr);
            endpoints.push_front (ep);
         }

         /*!
          * Remove the entry in @c ep, from the list of end-points connected to the
          * transport layer.
          *
          * If @c ep is equal to @c nullptr then all end-points are removed.
          *
          * @param [in] ep pointer to the end-point entry to remove or @c nullptr to
          *             remove all entries.
          */
         void remove (HF::Transport::Endpoint *ep = nullptr)
         {
            if (ep != nullptr)
            {
               endpoints.remove (ep);
            }
            else
            {
               endpoints.clear ();
            }
         }

         /*!
          * Receive the data in @c payload, coming in in the given @c link and
          * deliver the decoded packet to all registered end-points.
          *
          * @param [in] link     pointer to the link the incoming data was received.
          * @param [in] payload  reference to the ByteArray containing the data received.
          */
         void receive (HF::Transport::Link *link, HF::Common::ByteArray &payload)
         {
            assert (link != nullptr);
            Protocol::Packet *packet = new Protocol::Packet ();
            packet->link = link;

            uint16_t offset = packet->unpack (payload);

            /* *INDENT-OFF* */
            std::for_each (endpoints.begin (), endpoints.end (),
                  [&packet, &payload, &offset](HF::Transport::Endpoint *ep)
                  {
                     ep->receive (*packet, payload, offset);
                  });
            /* *INDENT-ON* */

            delete packet;
         }

         const HF::UID::UID uid () const
         {
            return HF::UID::UID(_uid);
         }

         /*!
          * Set the UID to the given value.
          *
          * @param [in] _uid  pointer to the UID to use.
          */
         void uid (HF::UID::UID_T *_uid)
         {
            this->_uid = _uid;
         }

         /*!
          * Call the @c connected method for all the registered end-points
          * with the given @c link as argument.
          *
          * @param [in] link  pointer to the link to call the @c connected method with.
          */
         void connected (HF::Transport::Link *link)
         {
            assert (link != nullptr);

            /* *INDENT-OFF* */
            std::for_each (endpoints.begin (), endpoints.end (),
                  [link](HF::Transport::Endpoint *ep)
                  {
                     ep->connected (link);
                  });
            /* *INDENT-ON* */
         }

         /*!
          * Call the @c disconnected method for all the registered end-points
          * with the given @c link as argument.
          *
          * @param [in] link  pointer to the link to call the @c disconnected method with.
          */
         void disconnected (HF::Transport::Link *link)
         {
            assert (link != nullptr);

            /* *INDENT-OFF* */
            std::for_each (endpoints.begin (), endpoints.end (),
                  [link](HF::Transport::Endpoint *ep)
                  {
                     ep->disconnected (link);
                  });
            /* *INDENT-ON* */
         }
      };

      /*! @} */

   }  // namespace Transport

}  // namespace HF

#endif /* HF_TRANSPORT_H */
