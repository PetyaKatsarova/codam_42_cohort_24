#ifndef SAMPLE_CLASS_H
# define SAMPLE_CLASS_H

class Sample {
    public:

        Sample(int val); // constructor
        ~Sample(void); // destructor

        int getBla(void) const;
        int compare(Sample *other) const;

    private:

        int _bla;
};

#endif