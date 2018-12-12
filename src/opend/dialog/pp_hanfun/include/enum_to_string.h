#undef DECL_ENUM_ELEMENT
#undef DECL_ENUM_ELEMENT_VAL
#undef DECL_ENUM_ELEMENT_STR
#undef DECL_ENUM_ELEMENT_VAL_STR
#undef BEGIN_ENUM
#undef END_ENUM

#ifndef GENERATE_ENUM_STRINGS
    #define DECL_ENUM_ELEMENT( element ) element,
    #define DECL_ENUM_ELEMENT_VAL( element, value ) element = value,
    #define DECL_ENUM_ELEMENT_STR( element, descr ) DECL_ENUM_ELEMENT( element )
    #define DECL_ENUM_ELEMENT_VAL_STR( element, value, descr ) DECL_ENUM_ELEMENT_VAL( element, value )
    #define BEGIN_ENUM( ENUM_NAME ) typedef enum tag##ENUM_NAME
    #define END_ENUM( ENUM_NAME ) ENUM_NAME; \
            const char* GetString##ENUM_NAME(enum tag##ENUM_NAME index);
#else
    #define BEGIN_ENUM( ENUM_NAME) const char * GetString##ENUM_NAME( enum tag##ENUM_NAME index ) {\
        switch( index ) {
    #define DECL_ENUM_ELEMENT( element ) case element: return #element; break;
    #define DECL_ENUM_ELEMENT_VAL( element, value ) DECL_ENUM_ELEMENT( element )
    #define DECL_ENUM_ELEMENT_STR( element, descr ) case element: return descr; break;
    #define DECL_ENUM_ELEMENT_VAL_STR( element, value, descr ) DECL_ENUM_ELEMENT_STR( element, descr )

    #define END_ENUM( ENUM_NAME ) default: return "Unknown value"; } } ;

#endif
