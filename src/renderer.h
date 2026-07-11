#include <glad/glad.h>

class Renderer {
    private:
        bool isWireframeEnabled = false;
    public:
        void toggleWireFrame() {
            if (!isWireframeEnabled) {
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
                isWireframeEnabled = true;
            }
            else {
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                isWireframeEnabled = false;
            }
        }
};