#ifndef MBUTTONEVENTEMITTER_H
#define MBUTTONEVENTEMITTER_H
#include <string>

class MButtonEventEmitter
{
public:
    ~MButtonEventEmitter();
     static MButtonEventEmitter& getSingleton();
     static MButtonEventEmitter* getSingletonPtr();
     static void releaseSingleton();

     //event emitters
     void emitClicked(const std::string &entityName);
     void emitEnter(const std::string &entityName);
     void emitLeave(const std::string &entityName);

private:
     MButtonEventEmitter();
     MButtonEventEmitter(MButtonEventEmitter const&);
     MButtonEventEmitter& operator=(MButtonEventEmitter const&);
     static MButtonEventEmitter*    smInstance;
};

#endif // MBUTTONEVENTEMITTER_H
