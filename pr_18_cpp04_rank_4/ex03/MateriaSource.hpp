#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
private:
    AMateria* learned[4];
    static const int MAX_LEARN = 4;

public:
    MateriaSource();
    MateriaSource(const MateriaSource& other);
    virtual ~MateriaSource();
    
    MateriaSource& operator=(const MateriaSource& other);
    
    void learnMateria(AMateria*);
    AMateria* createMateria(std::string const & type);
};
#endif