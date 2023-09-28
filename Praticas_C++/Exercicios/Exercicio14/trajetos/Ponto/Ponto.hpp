#ifndef PONTO_HPP
#define PONTO_HPP
class Ponto {
   public:
    // Constructors
    Ponto(const double coordX, const double coodY);

    // Destructor
    virtual ~Ponto() = default;

    // Getters
    inline double getCoordX() const { return this->coordX; }
    inline double getCoordY() const { return this->coordY; }

   private:
    const double coordX;
    const double coordY;
};
#endif
