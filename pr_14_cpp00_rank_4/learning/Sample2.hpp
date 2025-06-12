#ifndef SAMPLE2_H
# define SAMPLE2_H

class Sample2 {
    public:

        char    a1;
        int     a2;
        float   a3;
        float   const q4;

        Sample2(char p1, int p2, float p3); // constructor
        ~Sample2(void); // destructor

        void bar(void) const;
};

#endif