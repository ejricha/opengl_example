// Movement.h
//
// Handle movement keys

#include <iostream>

// Position is from -1 to 1 in all dimension
using Position_t = float;
struct Position {
	Position_t x;
	Position_t y;
	Position_t z;
	Position() : x(0), y(0), z(0) {
	}
};
inline std::ostream& operator<<(std::ostream& os, const Position& p) {
	return (os << "(" << p.x << ", " << p.y << ", " << p.z << ")");
}

// Class holding a parameter
using Parameter_t = int8_t;
constexpr Parameter_t ParameterMax = 100;
class Parameter {
public:
	// Constructor
	Parameter() : _val(0), paused(false) {
	}

	// Get the value, unless we're paused
	Parameter_t Get() const {
		return (paused ? 0 : _val);
	}

	// Increment, but clip to min/max
	void Increment(const Parameter_t delta) {
		if (_val + delta > ParameterMax)
		{
			_val = ParameterMax;
			return;
		}
		if (_val + delta < -ParameterMax)
		{
			_val = -ParameterMax;
			return;
		}
		_val += delta;
	}
	
	// Keep the value, but return 0 when queried
	void Pause(bool should_pause) {
		paused = should_pause;
	}

private:
	Parameter_t _val;
	bool paused;
};
inline std::ostream& operator<<(std::ostream& os, const Parameter& p) {
	return (os << static_cast<int64_t>(p.Get()));
}

// Simple struct that holds 3 dimensions of a requested value
using Request_t = int8_t;
struct Request
{
	Parameter x;
	Parameter y;
	Parameter z;
	Request() : x(), y(), z() {
	}
};
inline std::ostream& operator<<(std::ostream& os, const Request& r) {
	return (os << "[" << r.x << " " << r.y << " " << r.z << "]");
}

// Class that holds current values in all directions
class Movement
{
public:
	// Constructor
	Movement() : pos(), vel() {
	}

	// Getters
	inline Request_t GetX() const {
		return pos.x;
	}
	inline Request_t GetY() const {
		return pos.y;
	}
	inline Request_t GetZ() const {
		return pos.z;
	}

	// Setters
	inline void IncrementVelocityX(const Request_t delta) {
		vel.x.Increment(delta);
	}
	inline void IncrementVelocityY(const Request_t delta) {
		vel.y.Increment(delta);
	}
	inline void IncrementVelocityZ(const Request_t delta) {
		vel.z.Increment(delta);
	}

	// Print the values
	void Print() {
		std::cout << "Position:" << pos << " ; Velocity:" << vel << "\n";
	}
private:
	// Member variables
	Position pos; // position
	Request vel; // velocity
};
