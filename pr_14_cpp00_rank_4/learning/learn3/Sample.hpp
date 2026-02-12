#ifndef SAMPLE_CLASS_H
# define SAMPLE_CLASS_H

class Sample {
    public:

        Sample(); // constructor
        ~Sample(void); // destructor

       static int   getNumInst(void);

    private:

        static int  _numInst;
};

#endif