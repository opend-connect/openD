// =============================================================================
/*!
 * @file       apps/transport.h
 *
 * This file contains the declarations of the transport layer over libuv.
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

#ifndef HF_APP_TRANSPORT_H
#define HF_APP_TRANSPORT_H

#include <forward_list>

#include "uv.h"

#include "hanfun.h"

// =============================================================================
// API
// =============================================================================

namespace HF
{
   /*!
    * @addtogroup examples
    */

   namespace Application
   {
      /*!
       * Transport Layer implementation over TCP/IP using libuv.
       */
      class Transport:public HF::Devices::Concentrator::Transport
      {
         protected:

         uv_tcp_t socket;  //!< libuv tcp/ip socket.

         public:

         virtual ~Transport() {}

         void initialize ();

         void destroy ();
      };

      /*!
       * Transport Layer link implementation over TCP/IP using libuv.
       */
      class Link:public HF::Transport::AbstractLink
      {
         protected:

         Transport *tsp;   //!< Transport layer for this link.

         uv_stream_s *stream; //!< libuv stream to send/receive messages.

         public:

         /*!
          * Constructor.
          *
          * @param _tsp    pointer to the transport layer.
          * @param stream  pointer to the libuv stream.
          */
         Link(Transport *_tsp, uv_stream_s *stream):
            HF::Transport::AbstractLink (), tsp (_tsp), stream (stream)
         {
            stream->data = this;
         }

         virtual ~Link()
         {}

         void send (HF::Common::ByteArray &array);

         Transport *transport () const
         {
            return tsp;
         }
      };

   }  // namespace Application

   /*! @} */

}  // namespace HF

#endif /* HF_TRANSPORT_H */
