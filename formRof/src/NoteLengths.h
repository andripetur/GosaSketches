//
//  NoteLengths.h
//  formRof
//
//  Created by Andri Pétur Þrastarson on 16/03/15.
//
//

#ifndef __formRof__NoteLengths__
#define __formRof__NoteLengths__

class NoteLengths
{
public:
    NoteLengths();
    NoteLengths(float bpm);
    
    enum noteLengths
    {
        _1n, _2n,
        _4n, _8n,
        _16n, _32n,
        _64n, _128n,
        NR_NLENGTHS
    };
    
    float getValue(int which);
    float getBpm();
    
    void setBpm(float bpm);
    
    
private:
    void calculateNoteLengths();
    
    float bpm;
    float nLengths[NR_NLENGTHS];
    
};
#endif /* defined(__formRof__NoteLengths__) */
