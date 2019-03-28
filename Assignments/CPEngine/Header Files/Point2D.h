#pragma once
#pragma once
/**
 Point2D.h
 purpose: Library File to create a 2D point in space
 @author Mit Doshi
 @version 1.1 09/15/2018
*/

/**
	Point2D class for creating a point in 2D space
*/
class Point2D {
	
public:
	Point2D(float i_x, float i_y) {
		m_x = i_x;
		m_y = i_y;
	}

	Point2D() {
		m_x = 0;
		m_y = 0;
	}

	float X() const { return m_x; }
	float Y() const { return m_y; }

	void X(const float i_x) { m_x = i_x; }
	void Y(const float i_y) { m_y = i_y; }

	/**
		Operator function to copy value from one Point2D object to another
		@param i_value the Point2D value which is to be copied
	*/
	Point2D& operator=(const Point2D i_rhs) {
		this->m_x = i_rhs.X();
		this->m_y = i_rhs.Y();
		return *this;
	}

	Point2D& operator=(const Point2D *i_rhs) {
		this->m_x = i_rhs->X();
		this->m_y = i_rhs->Y();
		return *this;
	}


	/**
		operator function to add 2 Point2D classes

		@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	Point2D& operator+=(const Point2D &i_rhs) {
		this->m_x += i_rhs.X();
		this->m_y += i_rhs.Y();
		return *this;
	}
	

	/**
		operator function to subtract 2 Point2D classes

		@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	Point2D& operator-=(const Point2D &i_rhs) {
		this->m_x -= i_rhs.X();
		this->m_y -= i_rhs.Y();
		return *this;
	}

	/**
		operator function to multiply 2 Point2D classes

		@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	Point2D& operator*=(const Point2D &i_rhs) {
		this->m_x *= i_rhs.X();
		this->m_y *= i_rhs.Y();
		return *this;
	}

	/**
		operator function to divide 2 Point2D classes

		@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	Point2D& operator/=(const Point2D &i_rhs) {
		this->m_x /= i_rhs.X();
		this->m_y /= i_rhs.Y();
		return *this;
	}

	/**
	operator function to add 2 Point2D classes

	@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	inline Point2D operator+(const Point2D &i_rhs) {
		return Point2D(X() + i_rhs.X(), Y() + i_rhs.Y());
	}

	/**
	operator function to subtract 2 Point2D classes

	@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	inline Point2D operator-(const Point2D &i_rhs) {
		return Point2D(X() - i_rhs.X(), Y() - i_rhs.Y());
	}

	/**
	operator function to multiply 2 Point2D classes

	@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	inline Point2D operator*(const Point2D &i_rhs) {
		return Point2D(X() * i_rhs.X(), Y() * i_rhs.Y());
	}

	/**
	operator function to divide 2 Point2D classes

	@param i_rhs referenced variable of Point2D which is on Right hand side
	*/
	inline Point2D operator/(const Point2D &i_rhs) {
		return Point2D(X() / i_rhs.X(), Y() / i_rhs.Y());
	}

	/**
	operator function to add a Point2D class with any integer

	@param i_rhs referenced value of integer which is on Right hand side
	*/
	inline Point2D operator+(const float &i_rhs) {
		return Point2D(X() + i_rhs, Y() + i_rhs);
	}

	/**
	operator function to subtract a Point2D class with any integer

	@param i_rhs referenced variable of integer which is on Right hand side
	*/
	inline Point2D operator-(const float &i_rhs) {
		return Point2D(X() - i_rhs, Y() - i_rhs);
	}

	/**
	operator function to multiply a Point2D class with any integer

	@param i_rhs referenced variable of integer which is on Right hand side
	*/
	inline Point2D operator*(const float &i_rhs) {
		return Point2D(X() * i_rhs, Y() * i_rhs);
	}

	/**
	operator function to divide a Point2D class with any integer

	@param i_rhs referenced variable of integer which is on Right hand side
	*/
	inline Point2D operator/(const float &i_rhs) {
		return Point2D(X() / i_rhs, Y() / i_rhs);
	}

	inline Point2D operator/=(const float &i_rhs) {
		return Point2D(X() / i_rhs, Y() / i_rhs);
	}

	bool operator ==(Point2D const &rhs) {
		if (X() == rhs.X() && Y() == rhs.Y()) {
			return true;
		}
		else {
			return false;
		}
	}

	static const Point2D Zero;
	static const Point2D Unit;
	static const Point2D Unit_Negative;

private:
	float m_x;
	float m_y;
};