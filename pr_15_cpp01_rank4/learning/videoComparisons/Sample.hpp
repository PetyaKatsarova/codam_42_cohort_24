#ifndef SAMPLE_CLASS_H
#define SAMPLE_CLASS_H

class Sample {

    public:

        Sample(int num); // constructor
        ~Sample(void); // destructor

        int getFoo(void) const; //doesnt change the obj
        int compare(const Sample *other) const;

        private:

            int _foo;
};

#endif