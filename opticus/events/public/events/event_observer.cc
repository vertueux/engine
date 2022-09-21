#include "events/event_observer.h"

using std::vector;
using std::unique_ptr;

int EventHandler::counter;

void EventHandler::operator()() {
    this->_func();
}

void EventHandler::operator=(const EventHandler &func) {
    if(this->_func == nullptr) {
        this->_func = func;
        this->id = ++EventHandler::counter;
    } else {
        // Throw as exception or just log it out.
        std::cerr << "Nope!" << std::endl;
    }
}

bool EventHandler::operator==(const EventHandler &del) {
    return this->id == del.id;
}
bool EventHandler::operator!=(nullptr_t) {
    return this->_func != nullptr;
}


void Event::notify_handlers() {
    vector<unique_ptr<EventHandler>>::iterator func = this->handlers.begin();
    for(; func != this->handlers.end(); ++func) {
        if(*func != nullptr && (*func)->id != 0) {            
            (*(*func))();
            std::cout << "EventHandler.id: " << (*func)->id << std::endl;
        }
    }
}

void Event::add_handler(const EventHandler &handler) {
    this->handlers.push_back(unique_ptr<EventHandler>(new EventHandler{handler}));
}

void Event::remove_handler(const EventHandler &handler) {
    vector<unique_ptr<EventHandler>>::iterator to_remove = this->handlers.begin();
    for(; to_remove != this->handlers.end(); ++to_remove) {
        if(*(*to_remove) == handler) {
            std::cout << "Removing: " << (*to_remove)->id << std::endl;
            this->handlers.erase(to_remove);
            break;
        }
    }
}

void Event::operator()() {
    this->notify_handlers();
}

Event &Event::operator+=(const EventHandler &handler) {
    this->add_handler(handler);

    return *this;
}

Event &Event::operator+=(const EventHandler::Func &handler) {
    this->add_handler(EventHandler{handler});

    return *this;
}

Event &Event::operator-=(const EventHandler &handler) {
    this->remove_handler(handler);

    return *this;
}