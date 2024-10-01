#include <box2d/box2d.h>
#include <cstdint>  // for uintptr_t

class MyContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        // Retrieve the user data and cast uintptr_t back to void*
        void* userDataA = reinterpret_cast<void*>(bodyA->GetUserData().pointer);
        void* userDataB = reinterpret_cast<void*>(bodyB->GetUserData().pointer);

        // Example: Check if user data is valid and handle it
        if (userDataA) {
            // Handle user data for bodyA
        }
        if (userDataB) {
            // Handle user data for bodyB
        }
    }

    void EndContact(b2Contact* contact) override {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        b2Body* bodyA = fixtureA->GetBody();
        b2Body* bodyB = fixtureB->GetBody();

        // Retrieve and cast user data
        void* userDataA = reinterpret_cast<void*>(bodyA->GetUserData().pointer);
        void* userDataB = reinterpret_cast<void*>(bodyB->GetUserData().pointer);

        // Handle end of contact
    }

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {
        // Modify contact properties before solving (optional)
    }

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {
        // Access collision impulse values (optional)
    }
};
