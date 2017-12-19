# UDP message format

# Introduction

This page defines the message format used for inter-process communications between an application and the openD API on the fixed part side. The openD inter-process communication uses `JSON` objects over UDP transport as data-interchange mechanism.

The `JSON` syntax is specified [here](http://www.ecma-international.org/publications/files/ECMA-ST/ECMA-404.pdf
).

# JSON format

The generic JSON object format for an openD message is defined as follows:

```json
{
    "opend": {
        "version": "1.0.0",
        "message": {
            // Here the specific message is defined.
            "module": "audio"|"call"|"hanfun"|"mgmt"|"sixlowpan"|"sub",
            "primitive": "request"|"confirm"|"indication",
            "service": "Specific service name as string",
            "parameters": {
                // Parameters of the specific service.
            }
        }
    }
}
```

| Key  | Description |
| ----- | ----------- |
| `version`  | Defines the openD JSON API version.  |
| `message`  | Defines the message.  |
| `module`  | Defines which module relates to this message.  |
| `primitive`  | Defines the primitive type of this message. Currently there are three types of primitives: `request`, `confirm` and `indication` |
| `service`  | Defines the specific service within the specific message. This corresponds to the enumeration of the service of the specific module.  |
| `parameters`  | Defines the parameters of the specific service.  |

# Example

This example describes a message of a subscription request of the subscription module. As module name `module` the abbreviation of the `subscription` module is used. The key/value pair `"primitive": "request"` determines that the current message is a request. The pair `service` describes the respective service of this message. Parameters required by the `subscribe` service are defined inside the `parameters` object.

```json
{
    "opend": {
        "version": "1.0.0",
        "message": {
            "module": "sub",
            "primitive": "request",
            "service": "subscribe",
            "parameters": {
                "rfpi": "0x1234567890",
                "ac": "0xAABBCCDD",
            }
        }
    }
}
```
