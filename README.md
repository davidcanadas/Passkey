# Passkey
Better C++ friendship at the function level.

A passkey is a way to provide function-level friendship between classes. You can think of it like a lock that only a certain group of handpicked classes know how to open.

This is generally known as _the passkey idiom_, as suggested in https://www.spiria.com/en/blog/desktop-software/passkey-idiom-and-better-friendship-c/ and https://arne-mertz.de/2016/10/passkey-idiom/, among others.

However, what I personally did not like about those proposals is that the passkey type is a template, which forces functions protected by the passkey to (indirectly) know the type of the class granted, as in traditional C++ friendship. Also, since friendship doesn't work well with variadic template arguments, you must overload the protected function for each passkey you want to grant access to.

This passkey implementation is not based on templates but on preprocessor macros. This is generally a less elegant approach, however it has some advantages: classes that implement locked functions do not need to know which classes can open the lock; also one key can be used to grant access to multiple classes.

## How to declare a passkey

Passkeys are to be declared in a file known by the classes allowed to open the lock.

Start the passkey declaration with `PK_BEGIN(<PASSKEYNAME>)`; where `<PASSKEYNAME>` is the name of the passkey. By convention, it is recommended to name the passkey after the type of behavior to protect (ex: `AllocatePasskey`) and not the class to unprotect; as one class can require multiple passkeys for different functions.

Grant other types to open the passkey with `PK_ALLOW(<TYPENAME>)`; where `<TYPENAME>` is the type granted to use the passkey.

Close the passkey declaration with `PK_END`.

Typenames used in these macros can be forward-declared; no need to declare or include them in any way.

Feel free to declare passkeys in the namespace of your choice. Do not introduce any other macros or code between those.

Example:
    
    PK_BEGIN(BazPasskey)
        PK_ALLOW(FooClass)
        PK_ALLOW(BarClass)
    PK_END

## How to require a passkey

Passkeys are to be forward-delcared when declaring classes with functions protected by passkeys.

Protected functions do require to receive a nameless, constant reference of the passkey. By convention, it is recommended to put them as the last argument in the arguments list, for instance:

    void BazClass::FooFunction(int _Bar, const BazPasskey&);

## How to use a passkey

A class requiring access to a function protected by a passkey needs to pass a passkey reference:

    BazInstance->FooFunction(0, BazPasskey());

Any attempt to build a passkey by a unallowed class will generate a compilation error.
