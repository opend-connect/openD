/*
 * Copyright (C) 2018 by Dialog Semiconductor. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Dialog Semiconductor nor the names of its Affiliates
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef HF_ULE_H
#define HF_ULE_H

// #include "hanfun/transport.h"
#include <hanfun.h>
#include <list>           // std::list
#include <deque>          // std::queue
#include <queue>          // std::queue

extern "C"
{
#include "mmi_def.h"
}

namespace HF
{
   /*!
    * This is the top-level namespace for the HAN-FUN transport layer using the
    * ULE technology.
    */
   namespace ULE
   {
      class Transport;

      /*!
       *
       */
      class Link: public HF::Transport::AbstractLink
      {
            Transport * _layer;

            HF::UID::DECT _uid;

         public:

            Link (Transport * _layer) :
               _layer (_layer)
            {
            }

            const HF::UID::UID uid () const
            {
               return HF::UID::UID((HF::UID::UID_T *)&_uid);
            }

            void uid (HF::UID::DECT &rfpi)
            {
               _uid = rfpi;
            }

            HF::Transport::Layer const *transport () const
            {
               return (HF::Transport::Layer const *)_layer;
            }

            void send (HF::Common::ByteArray &payload);
      };

      class Queue
      {
         std::vector<HF::Common::ByteArray>  db;

         public:

         Queue () : db(std::vector<HF::Common::ByteArray>())
         {}

         void push(HF::Common::ByteArray &payload)
         {
            db.push_back(payload);
         }

         void pop()
         {
            db.erase(db.begin());
         }

         HF::Common::ByteArray &front()
         {
            return db.front();
         }

         size_t size() const
         {
            return db.size(); // std::distance(db.begin(), db.end());
         }

         bool empty() const
         {
            return db.empty();
         }
      };


      /*!
       *
       */
      class Transport: public HF::Devices::Node::Transport
      {
            HF::UID::DECT _uid;
            bool _transport_init;
            Queue tx_queue;

         public:

            // Transport () : tx_queue(Queue ())
            // {_transport_init = 0;}

            static Transport * instance();

            virtual ~Transport ()
            {}

            void configure (char* part_name);

            void initialize ();

            bool is_initialized () {
            	return _transport_init;
            }

            void destroy ();

            const HF::UID::UID uid () const
            {
               return HF::UID::UID((HF::UID::UID_T *)&_uid);
            }

            void uid (HF::UID::DECT &ipui)
            {
               _uid = ipui;
            }

            void receive (const rsuint8 *data, size_t size);

            void connected ();

            /*!
             * Check base for new data.
             */
            void check();

            /*!
             * Schedule payload to be delivered to the base.
             *
             * @param [in] payload  data to be delivered to the base.
             */
            void deliver(HF::Common::ByteArray &payload);

            /*!
             * Indicate result for last data transmitted.
             *
             * @param [in] result   last data transmitted result.
             */
            void delivered(bool result = true);

         protected:

            bool is_stack_ready()
            {
               return !((MmiCtrl.islocked == 0) || (MmiCtrl.UleReadyReceived == 0) || (MmiCtrl.pvc == 1));
            }

            bool is_tx_pending()
            {
               return MmiCtrl.PendTDR != 0;
            }

            void send();

         private:

            Transport () : tx_queue(Queue ())
            {_transport_init = 0;}

            Transport(Transport const&); // Don't Implement
            void operator= (Transport const&); // Don't implement
      };

   } // namespace ULE

} // namespace HF

/**
 * @brief   Success confirmation indication.
 *
 * @details Success confirmation and indication led blinking.
 */
void successConInd();

/**
 * @brief   Failure confirmation indication.
 *
 * @details Failure confirmation and indication led blinking.
 */
void failureConInd();

/**
 * @brief   Exit app.
 *
 * @details Exit application and destroy transport layer.
 */
void exitApp();

#endif /* HF_ULE_H */
