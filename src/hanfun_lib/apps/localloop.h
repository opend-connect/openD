// =============================================================================
/*!
 * @file       apps/localloop.h
 *
 * This file contains an implementation of a HAN-FUN transport layer to be used
 * in the example applications.
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

#ifndef HF_APP_LOCALLOOP_H
#define HF_APP_LOCALLOOP_H

#include "hanfun.h"

namespace
{
   /*!
    * Local network link.
    */
   struct Link:public HF::Transport::AbstractLink
   {
      HF::Transport::AbstractLayer &recv_tsp;

      HF::UID::UID_T               *_uid;
      HF::Transport::Layer         *tsp;

      Link                         *other;

      Link(HF::Transport::AbstractLayer &_recv_tsp,
           HF::UID::UID_T *uid = new HF::UID::NONE (),
           HF::Transport::Layer *tsp = nullptr):
         recv_tsp (_recv_tsp), _uid (uid), tsp (tsp), other (nullptr)
      {}

      virtual ~Link()
      {
         delete _uid;
      }

      void send (HF::Common::ByteArray &array)
      {
         recv_tsp.receive (other, array);
      }

      const HF::UID::UID uid () const
      {
         return HF::UID::UID(_uid);
      }

      HF::Transport::Layer const *transport () const
      {
         return tsp;
      }
   };

   /*!
    * This class holds the transport layers for the
    * concentrator (a.k.a. base) and the nodes.
    *
    * It is used to create the links between the concentrator and the nodes.
    */
   class Localloop
   {
      protected:

      //! Transport layer for the concentrator.
      HF::Devices::Concentrator::Transport base_tsp;

      //! Transport layers for the nodes.
      std::vector <HF::Devices::Node::Transport *> devices_tsp;

      public: ~Localloop()
      {
         base_tsp.destroy ();

         while (!devices_tsp.empty ())
         {
            auto tsp = devices_tsp.back ();
            tsp->destroy ();
            devices_tsp.pop_back ();
            delete tsp;
         }
      }

      /*!
       * Set the base of the network.
       *
       * @param [in] base  concentrator instance to use as the network base.
       */
      void set_base (HF::IDevice *base)
      {
         base_tsp.destroy ();
         base_tsp.add (base);
      }

      void add_node (HF::IDevice *node, std::string uid)
      {
         HF::Devices::Node::Transport *dev_tsp = new HF::Devices::Node::Transport ();
         dev_tsp->add (node);

         Link *dev_link  = new Link (base_tsp, new HF::UID::URI ("base"));
         Link *base_link = new Link (*dev_tsp, new HF::UID::URI (uid));

         dev_link->other  = base_link;
         base_link->other = dev_link;

         dev_tsp->add (dev_link);
         base_tsp.add (base_link);

         devices_tsp.push_back (dev_tsp);
      }
   };

}  // namespace

#endif /* HF_APP_LOCALLOOP_H */
