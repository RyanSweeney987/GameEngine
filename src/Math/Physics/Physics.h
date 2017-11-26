#pragma once

namespace AirEngine {
	namespace Math {
		namespace Physics {
			struct State {
				float pos;
				float vel;
			};
			struct Derivative {
				float derPos;
				float derVel;
			};

			class Physics {
			public:
				Derivative evaluate(const State& initial, float time);
				Derivative evaluate(const State& initial, float time, float deltaTime, Derivative& derivative);
				float acceleration(const State& state, float time);
				void integrate(State& state, float time, float deltaTime);
				State interpolate(const State& previous, const State& current, float alpha);
			private:
				float time;
				float deltaTime;
			};
		}
	}
}

// Force = mass * acceleration
// Acceleration = force / mass
// Velocity = acceleration (rate of change of position over time)