#include "GameObject.h"
#include "../Ensemble.h"


namespace Gelgine {
    GelgineContext *GameObject::getContext() {
        return ensemble->getContext();
    }
}