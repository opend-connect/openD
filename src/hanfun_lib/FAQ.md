# FAQ

# Frequently Asked Questions
____

__Q1 : I have updated my HAN-FUN library and now my application callbacks are not being called ?__

The signature for the callback methods may have changed. Please look for warnings indicating that
a _virtual_ function is being overloaded.

Also if you always call the parent's callback implementation (see bellow) you should receive a
warning if the method signature you are using has been deprecated.

        struct AlertSink:public HF::Units::Unit <HF::Profiles::Alertable>
        {
           // ...

           void status (HF::Protocol::Address &source, HF::Interfaces::Alert::Message &message)
           {
              // Call parent's implementation.
              HF::Units::Unit <HF::Profiles::Alertable>::status (source, message);

              // ...
           }

           // ...
        };

__Q2 : Can the HAN-FUN library be linked into a shared library ?__

Yes, however you must pass the __HF_SHARED_SUPPORT__ option when configuring the library.
This option will remove the flag '-fno-rtti' and add the '-fPIC' flag from the compilations flags.

The building instructions become :

      $ mkdir build/
      $ cd build/
      $ cmake -DHF_SHARED_SUPPORT=ON ..
      $ make
