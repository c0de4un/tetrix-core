/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// HEADER
#ifndef TETRIX_CORE_GAME_HPP
    #include <tetrix/core/game/TetrixGame.hpp>
#endif /// !TETRIX_CORE_GAME_HPP

// Include hex::core::Graphics
#ifndef HEX_CORE_GRAPHICS_SYSTEM_HPP
    #include <hex/core/graphics/GraphicsSystem.hpp>
#endif /// !HEX_CORE_GRAPHICS_SYSTEM_HPP

// Include hex::core::AssetsSystem
#ifndef HEX_CORE_ASSETS_SYSTEM_HPP
    #include <hex/core/assets/AssetsSystem.hpp>
#endif /// !HEX_CORE_ASSETS_SYSTEM_HPP

#ifdef HEX_LOGGING /// LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TetrixGame
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace tetrix
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        TetrixGame::TetrixGame()
            :
            Application()
        {
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        TetrixGame::~TetrixGame() noexcept
        {
            stopGame();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.ISystem
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool TetrixGame::onStart()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("TetrixGame::onStart");
#endif // LOG

            // Start Graphics & Renderer
            auto graphics(hexGraphics::getInstance());
#ifdef HEX_DEBUG // DEBUG
            assert(graphics.get() && "TetrixGame::onStart: graphics is null");
            assert((!graphics->isStarted() && !graphics->isPaused()) && "TetrixGame::onStart: invalid graphics state");
#endif // DEBUG

            // @TODO: Register Game as IRendererListener

            bool startResult(graphics->Start());
#ifdef HEX_DEBUG // DEBUG
            assert(startResult && "TetrixGame::onStart: failed to start graphics");
#else // !DEBUG
            return false;
#endif // DEBUG

            // Start AssetsSystem
            auto assetsSystem(hexAssets::getInstance());
            startResult = assetsSystem->Start();
#ifdef HEX_DEBUG // DEBUG
            assert(startResult && "TetrixGame::onStart: failed to start assets system");
#else // !DEBUG
            return false;
#endif // DEBUG

            return System::onStart();
        }

        bool TetrixGame::onResume()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("TetrixGame::onResume");
#endif // LOG

            // Resume Graphics
            auto graphics(hexGraphics::getInstance());
#ifdef HEX_DEBUG // DEBUG
            assert(graphics.get() && "TetrixGame::onResume: graphics is null");
#endif // DEBUG

            bool resumeResult(graphics->Start());

#ifdef HEX_DEBUG // DEBUG
            assert(resumeResult && "TetrixGame::onResume: failed to resumt graphics");
#else // !DEBUG
            return false;
#endif // DEBUG

            // Resume Assets
            auto assetsSystem(hexAssets::getInstance());
#ifdef HEX_DEBUG // DEBUG
            assert(assetsSystem.get() && "TetrixGame::onResume: assets is null");
#endif // DEBUG

            resumeResult = assetsSystem->Start();

#ifdef HEX_DEBUG // DEBUG
            assert(resumeResult && "TetrixGame::onResume: failed to resumt assets");
#else // !DEBUG
            return false;
#endif // DEBUG

            return System::onResume();
        }

        void TetrixGame::onPause()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("TetrixGame::onPause");
#endif // LOG

            // Pause Graphics
            auto graphics(hexGraphics::getInstance());
            if (graphics.get())
                graphics->Pause();

            // Pause Assets
            auto assetsSystem(hexAssets::getInstance());
            if (assetsSystem.get())
                assetsSystem->Pause();

            System::onPause();
        }

        void TetrixGame::onStop()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("TetrixGame::onStop");
#endif // LOG

            stopGame();

            System::onStop();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void TetrixGame::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("TetrixGame::onStart");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance.get() && "TetrixGame::Initialize: already initialized");
#endif // DEBUG

            if (!mInstance.get())
                mInstance = new TetrixGame();
        }

        void TetrixGame::stopGame() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("TetrixGame::stopGame");
#endif // LOG

            // Stop Graphics
            auto graphics(hexGraphics::getInstance());
            if (graphics.get())
                graphics->Pause();

            // Stop Assets
            auto assetsSystem(hexAssets::getInstance());
            if (assetsSystem.get())
                assetsSystem->Stop();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE: IRendererListener.PUBLIC
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool TetrixGame::onRenderReady()
        {
            //hexShared<hexAssets> assetsSystem(hexAssets::getInstance());

#ifdef HEX_DEBUG // DEBUG
            //assert(assetsSystem.get() && "TetrixGame::onRenderReady: AssetsSystem is not initialized");
#endif // DEBUG

            // @TODO: Create Material

            // @TODO: Load Fragment Shader
            
            // @TODO: Load Vertex Shader

            // @TODO: Create Triangle Mesh

            // @TODO: Create Triangle2D Object

            // @TODO: Attach Material & Mesh to Triangle2D object

            // @TODO: Create Camera2D

            // @TODO: Create Scene2D

            // @TOOD: Show Triangle2D

            return true;
        }

        void TetrixGame::onRender()
        {
        }

        void TetrixGame::onRenderError(const std::exception err)
        {
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
