// =============================================================================
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
// =============================================================================
#ifndef HF_DIALOG_H
#define HF_DIALOG_H


#include <hanfun.h>

// =============================================================================
// Defines
// =============================================================================

#define API_TASK 0x01

#define NO_COMPORT_USE -127
#define ULE_INIT_CONNECT_WITH_REPS      -2  // as defined in uleDectApi.h
#define ULE_INIT_CONNECT_ON_LINUX_HOST  -3  // as defined in uleDectApi.h

// Define this to disable Dialog Demo specific code
// Should be disabled for pure HanFun testing/verification
//#define DISABLE_VERIFICATION_CONFLICTS

void setBaseComport(int8_t comport);

void setBaseHdlcPortStr(std::string portname);

/*!
 * Set the concentrator dect mode.
 */
uint8_t changeConcentratorDectMode(uint8_t DectMode);

/*!
 * Reset the concentrator dect module.
 */
void resetConcentratorDectModule();

std::string getBaseRfpiString();

// =============================================================================
// Transport API
// =============================================================================

namespace HF
{
   /*!
    * Top-level namespace for all ULE transport specific classes and functionality.
    */
   namespace ULE
   {

      class Link;

      /*!
       * HAN-FUN Transport Layer API implementation using Dialog's ULE Stack.
       */
      class Transport: public HF::Devices::Concentrator::Transport
      {
         public:

         static Transport * instance();

         virtual ~Transport() {}

         void initialize ();

         void initialize (int8_t comport);

         void destroy ();

         void connected (uint16_t dev_id, uint8_t ipui[5]);

         void receive(const uint16_t dev_id, const uint8_t data[], size_t size);

         Link * find_by_id(uint16_t dev);

         Link * find_by_address(uint16_t address);

         private :

         Transport() {}
      };

      class Link: public HF::Transport::AbstractLink
      {
         protected:

         const uint16_t dev_id;

         Transport *tsp;

         HF::UID::DECT ipui;

         public:

         Link (uint16_t dev_id, HF::UID::DECT &_ipui, Transport *tsp) :
               HF::Transport::AbstractLink(), dev_id(dev_id), tsp(tsp), ipui(_ipui)
         {}

         virtual ~Link ()
         {
         }

         void send (HF::Common::ByteArray &array);

         const HF::UID::UID uid () const
         {
            return HF::UID::UID((HF::UID::UID_T *)&ipui);
         }

         void uid (const HF::UID::DECT &_ipui)
         {
            this->ipui = _ipui;
         }

         HF::Transport::Layer const *transport () const
         {
            return tsp;
         }

         uint16_t id()
         {
            return dev_id;
         }
      };

   }  // namespace ULE

}  // namespace HF

#endif /* HF_DIALOG_H */
