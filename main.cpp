#include <iostream>
#include <iomanip>

#include "sqrt/fisr.h"

int main() {
    using namespace std;

    cout << fixed << setprecision(15) << fisr(2);

    return 0;
}

// sqrt(2)
// G1   1.414567112922668
// G2   1.414213776588440
// G3   1.414213418960571
// G4   1.414213538169861 - 4 iterations is enough to get maximum precision (7)
// G100 1.414213538169861
// R    1.41421356237309504880168872420969807856967187537694

// 1 / sqrt(2)
// G1   0.7069300413
// G2   0.7071066499
// G3   0.7071068287
// G4   0.7071067691 - 4 iterations is enough to get maximum precision (7)
// G100 0.7071067690
// R    0.7071067812
