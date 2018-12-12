// =============================================================================
/*!
 * @file       tests/test_transport.cpp
 *
 * This file contains the implementation of the tests for the transport API.
 *
 * @version    1.3.0
 *
 * @copyright  Copyright &copy; &nbsp; 2014 Bithium S.A.
 *
 * For licensing information, please see the file 'LICENSE' in the root folder.
 */
// =============================================================================
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

#include "test_helper.h"

#include "hanfun/transport.h"

using namespace HF;

// =============================================================================
// Helper Classes
// =============================================================================
namespace HF
{
   namespace Testing
   {
      struct Endpoint:public HF::Transport::Endpoint
      {
         std::list <HF::Transport::Link *> links;

         virtual void connected (HF::Transport::Link *link)
         {
            links.push_back (link);
         }

         virtual void disconnected (HF::Transport::Link *link)
         {
            links.remove (link);
         }

         void receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
         {
            UNUSED (packet);
            UNUSED (payload);
            UNUSED (offset);
         }
      };

      struct Endpoint2:public Endpoint
      {
         void receive (Protocol::Packet &packet, Common::ByteArray &payload, uint16_t offset)
         {
            UNUSED (packet);
            UNUSED (payload);
            UNUSED (offset);
         }
      };

      struct Transport:public HF::Transport::Layer
      {
         std::list <HF::Transport::Endpoint *> endpoints;
         std::list <Link *>                    links;

         HF::UID::UID_T                        *_uid;

         Transport(HF::UID::UID_T *uid):
            _uid (uid)
         {}

         virtual ~Transport()
         {}

         // =============================================================================
         // API
         // =============================================================================

         virtual void initialize ()
         {}

         void add (HF::Transport::Endpoint *ep)
         {
            endpoints.push_back (ep);
         }

         void initialize (Endpoint *ep)
         {
            initialize ();
            add (ep);
         }

         void remove (HF::Transport::Endpoint *ep = nullptr)
         {
            if (ep != nullptr)
            {
               endpoints.remove (ep);
            }
            else
            {
               endpoints.erase (endpoints.begin (), endpoints.end ());
            }
         }

         void destroy ()
         {
            /* *INDENT-OFF* */
            for_each(links.begin(), links.end(), [this](Link *link)
            {
               this->destroy_link(link);

            });
            /* *INDENT-ON* */

            remove (nullptr);
         }

         const HF::UID::UID uid () const
         {
            return HF::UID::UID(_uid);
         }

         void create_link (HF::UID::UID_T *uid)
         {
            Testing::Link *link = new Testing::Link (uid, this);
            links.push_back (link);

            /* *INDENT-OFF* */
            for_each(endpoints.begin(), endpoints.end(), [link](HF::Transport::Endpoint *ep)
            {
               ep->connected (link);
            });
            /* *INDENT-ON* */
         }

         void destroy_link (Link * &link)
         {
            /* *INDENT-OFF* */
            for_each(endpoints.begin(), endpoints.end(), [link](HF::Transport::Endpoint *ep)
            {
               ep->disconnected (link);
            });
            /* *INDENT-ON* */

            delete link;
            link = nullptr;
         }
      };

   }  // namespace Testing

} // namespace Testing

// =============================================================================
// Transport API Tests.
// =============================================================================

TEST_GROUP (Transport)
{
   Testing::Endpoint  ep1;
   Testing::Endpoint2 ep2;

   HF::UID::URI tsp_uid;

   Testing::Transport *tsp;

   TEST_SETUP ()
   {
      tsp_uid = UID::URI ("tsp://foobar@example.com");
      tsp     = new Testing::Transport (&tsp_uid);

      mock ().ignoreOtherCalls ();
   }

   TEST_TEARDOWN ()
   {
      mock ("Link").checkExpectations ();
      tsp->destroy ();
      delete tsp;
      mock ().clear ();
   }
};

TEST (Transport, Initialize)
{
   LONGS_EQUAL (0, tsp->endpoints.size ());
   tsp->initialize (&ep1);
   LONGS_EQUAL (1, tsp->endpoints.size ());
   tsp->initialize (&ep2);
   LONGS_EQUAL (2, tsp->endpoints.size ());

   tsp->remove (&ep1);
   LONGS_EQUAL (1, tsp->endpoints.size ());
   tsp->initialize (&ep1);
   LONGS_EQUAL (2, tsp->endpoints.size ());

   tsp->destroy ();
   LONGS_EQUAL (0, tsp->endpoints.size ());
}

TEST (Transport, LinkSetup)
{
   tsp->initialize (&ep1);

   UID::URI *uri = new UID::URI ("dev://user1@example.com");

   tsp->create_link (uri);

   LONGS_EQUAL (1, ep1.links.size ());

   tsp->initialize (&ep2);

   uri = new UID::URI ("dev://user2@example.com");
   tsp->create_link (uri);

   LONGS_EQUAL (2, ep1.links.size ());
   LONGS_EQUAL (1, ep2.links.size ());

   tsp->destroy_link (tsp->links.back ());

   LONGS_EQUAL (1, ep1.links.size ());
   LONGS_EQUAL (0, ep2.links.size ());

   tsp->destroy_link (tsp->links.front ());

   LONGS_EQUAL (0, ep1.links.size ());
   LONGS_EQUAL (0, ep2.links.size ());
}
