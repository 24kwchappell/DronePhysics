#include <iostream>
#include <cctype>
#include <thread>

class Mass {
    public:
        const float m_mass;
        float m_net_force;
        float m_velocity;
        float m_height;

        Mass(float mass, float height) : m_mass(mass), m_net_force(0), m_velocity(0), m_height(height) {}

        friend std::ostream& operator<<(std::ostream&, const Mass&);
};

void physics(Mass&, float, float);

int main(void){
    const float dt = 1; // in seconds
    const float target = 1000; // in meters
    float elapsed = 0; // total time in seconds
    Mass obj(50, target/10); // weight, intial height 
    
    while(true){ 
        std::cout << obj << "Time Elapsed: " << elapsed << " second(s)\n";
        physics(obj, 0, dt);
        elapsed += dt;

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(dt * 1000)));
        if(obj.m_height >= target)
            break;
    }
    
    return EXIT_SUCCESS;
}

void physics(Mass& obj, float thrust, float dt){

    float gravityf = obj.m_mass * (-9.8f); // force of gravity
    obj.m_net_force = gravityf + thrust;

    float accel = obj.m_net_force / obj.m_mass; // a = F/m
    obj.m_height += obj.m_velocity * dt + (0.5 * accel * dt * dt); // Hf(t) = Hi + Vi(t) + 1/2a(t)^2
    obj.m_velocity += accel * dt; // Vf(t) = Vi + a(t)
    obj.m_height = [&]() -> float {
        const float ret = std::max(obj.m_height, 0.0f);
        if(ret == 0.0f)
            obj.m_velocity = 0.0f;
        return ret;
    }();
}

std::ostream& operator<<(std::ostream& stream, const Mass& obj){
    stream << "Object Height: " << obj.m_height << "m Velocity: " << obj.m_velocity << "m/s ";
    return stream;
}
