#include "Physics.h"

namespace AirEngine {
	namespace Math {
		namespace Physics {
			Derivative Physics::evaluate(const State & initial, float time) {
				Derivative output;
				output.derPos = initial.vel;
				output.derVel = acceleration(initial, time);
				return output;
			}

			Derivative Physics::evaluate(const State& initial, float time, float deltaTime, Derivative& derivative) {
				// Get current state and advance to time + delta time
				State state;
				state.pos = initial.pos + derivative.derPos * deltaTime;
				state.vel = initial.vel + derivative.derVel * deltaTime;

				Derivative output;
				output.derPos = state.pos;
				output.derVel = acceleration(state, time + deltaTime);

				return output;
			}

			float Physics::acceleration(const State& state, float time) {
				// Do simulation specific calculations here
				const float k = 100; // Spring? Force??
				const float b = 1.0f; // Damper? Mass??
				return -k * state.pos - b * state.vel;
			}

			void Physics::integrate(State& state, float time, float deltaTime) {
				Derivative a, b, c, d;

				a = evaluate(state, time, 0.0f, Derivative());
				b = evaluate(state, time, deltaTime * 0.5f, a);
				c = evaluate(state, time, deltaTime * 0.5f, b);
				d = evaluate(state, time, deltaTime, c);

				float deltaPosDeltaTime = 1.0f / 6.0f * (a.derPos + 2.0f * (b.derPos + c.derPos) + d.derPos);
				float deltaVelDeltaTime = 1.0f / 6.0f * (a.derVel + 2.0f * (b.derVel + c.derVel) + d.derVel);

				state.pos = state.pos + deltaPosDeltaTime * deltaTime;
				state.vel = state.vel + deltaVelDeltaTime * deltaTime;
			}

			State Physics::interpolate(const State& previous, const State& current, float alpha) {
				State state;
				state.pos = current.pos * alpha + previous.pos * (1 - alpha);
				state.vel = current.vel * alpha + previous.vel * (1 - alpha);
				return state;
			}
		}
	}
}