/**
 * @file
 * @brief     This class contains the Coordinate3D Class
 * @author    Jeroen van Hattem and Jeffrey de Waal
 * @license   See LICENSE
 */
#ifndef COORDINATE3D_HPP
#define COORDINATE3D_HPP


/**
 * @brief Coordinate3D class
 * 
 * This class is here, because it works easier than an array.
 * 
 */
class Coordinate3D {
  private:
    int x;
    int y;
    int z;

  public:
    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     */
    Coordinate3D() :
        x(0), y(0), z(0) {
    }
    /**
     * @brief Construct a new Coordinate3D object
     *
     * The default constructor to create a new Coordinate3D object.
     *
     * @param x : int
     * @param y : int
     * @param z : int
     *
     */
    Coordinate3D(int x, int y, int z) : x(x), y(y), z(z) {
    }  
    /**
     * @brief This function returns the X value of the coordinate
     *
     * @return int
     */
    int getX() {
        return x;
    }
    /**
     * @brief This function returns the Y value of the coordinate
     *
     * @return int
     */
    int getY() {
        return y;
    }
    /**
     * @brief This function returns the Z value of the coordinate
     *
     * @return int
     */
    int getZ() {
        return z;
    }
    /**
     * @brief This function sets the X variable to the value passed as parameter.
     *
     * @param value : int
     */
    void setX(int value) {
        x = value;
    }
    /**
     * @brief This function sets the Y variable to the value passed as parameter.
     *
     * @param value : int
     */
    void setY(int value) {
        y = value;
    }
    /**
     * @brief This function sets the Z variable to the value passed as parameter.
     *
     * @param value : int
     */
    void setZ(int value) {
        z = value;
    }

    Coordinate3D operator+(const Coordinate3D &other) const {
        Coordinate3D temp(*this);

        temp += other;

        return temp;
    }

    Coordinate3D operator-(const Coordinate3D &other) const {
        Coordinate3D temp(*this);

        temp -= other;

        return temp;
    }

    void operator+=(const Coordinate3D &other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator-=(const Coordinate3D &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    void operator=(const Coordinate3D &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    bool operator==(const Coordinate3D & other){
        if((x == other.x) && (y == other.y) && (z == other.z)) {
            return true;
        }
        return false;
    }
};

#endif // COORDINATE3D_HPP