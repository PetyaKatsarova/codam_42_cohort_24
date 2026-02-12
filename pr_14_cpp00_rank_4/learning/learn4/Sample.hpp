#ifndef SAMPLE_CLASS_H
# define SAMPLE_CLASS_H

class Sample {
    public:

        int num;

        Sample(void); // constructor
        ~Sample(void); // destructor

        void fun(void) const;
};

#endif