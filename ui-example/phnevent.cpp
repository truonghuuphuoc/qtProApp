#include "phnevent.h"

phnEvent::phnEvent(int zone, int target, int value, int sequence)
{
    this->Zone = zone;
    this->Target = target;
    this->Value = value;
    this->Sequence = sequence;
}
