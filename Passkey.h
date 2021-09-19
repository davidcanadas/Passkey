/**
 * @file    Passkey.h
 * @author  David Canadas Mazo
 */

#pragma once

/**
 * A passkey is a way to provide a function-level friendship between classes. You can think of it like a lock
 * that only a certain group of handpicked classes know how to open.
 * 
 * Classes holding the locked functions do not need to know which classes are able to open the lock.  This is
 * a huge advantage over C++ friendship, in which the class accepting the friendship request needs to know
 * which classes want to use the friendship.
 * 
 * How to declare a passkey:
 *      Passkeys are to be declared in a file known by classes habilitated to open the lock.
 *      Start  the passkey declaration with PK_BEGIN(<PasskeyName>).
 *      Unlock the passkey to classes and structures with PK_ALLOW(<Typename>).
 *      Commit the passkey declaration with PK_END.
 * Typenames used in these macros can be forward-declared, no need to declare or include them in any way.
 * Feel free to declare passkeys in the namespace of your choice. Do not introduce any other macros or code between those.
 * 
 * Example:
 *      PK_BEGIN(MyClassDefaultPasskey)
 *          PK_ALLOW(OneClass)
 *          PK_ALLOW(AnotherClass)
 *          PK_END
 * 
 * How to require a passkey:
 *      Passkeys are to be forward-declared when declaring classes protected by locks.
 *      Locked functions do require to receive a nameless, constant reference of the passkey. By convention, it is
 *      recommended to put them as the last argument in the chain, for instance:
 *          void MyClass::MyLockedFunction(int _foo, const MyClassDefaultPasskey&);
 * 
 * How to use a passkey:
 *      A class that wants to access a locked function just needs to pass an inline-constructed passkey, e.g.:
 *          aClassObject->MyLockedFunction(0, MyClassDefaultPasskey());
 * 
 *      If any class which can't unlock the passkey tries to build the passkey, the compiler will raise an error.
 */
#define PK_BEGIN(_PasskeyName)              \
    class _PasskeyName                      \
    {                                       \
    private:                                \
        _PasskeyName()                      { /* Intentionally blank */ }   \
        _PasskeyName(const _PasskeyName&)   { /* Intentionally blank */ }   \
        _PasskeyName& operator=(const _PasskeyName&) = delete;

#define PK_ALLOW(_ClassName)                \
    friend _ClassName;

#define PK_END                              \
    };//Passkey.
