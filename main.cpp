#include <iostream>
#include <ctime>
#include <Features/MCQStation.h>

#include "Application.h"
#include "Core/LeafStation.h"
#include "Editor/Editor.h"
#include "Schemas/McqChannelSchema.h"
#include "Serializers/StationNetworkSerializer.h"
#include "Units/VideoClip.h"

int main() {
    SPI::Application app;
    const SPI::Editor editor(app);

    const auto root = app.GetStationNetwork()->GetRoot();

    const auto id = editor.AddStation(0, SPI::STATION_TYPE::MCQ, 3.0);
    const auto station = std::dynamic_pointer_cast<SPI::MCQStation>(app.GetStationNetwork()->GetStationById(id));

    const auto leafId1 = editor.AddStation(id, SPI::STATION_TYPE::LEAF, 6.0);
    const auto leafId2 = editor.AddStation(id, SPI::STATION_TYPE::LEAF, 6.0);

    station->setQuestion("What is the capital of France?");
    station->setOption(0, "Paris");
    station->setOption(1, "London");
    station->setOption(2, "Berlin");

    const auto leafStation1 = app.GetStationNetwork()->GetStationById(leafId1);
    const auto leafStation2 = app.GetStationNetwork()->GetStationById(leafId2);

    const auto verse = app.GetStationNetwork()->GetRoot()->GetConnectedVerse(0);
    const auto verse2 = station->GetConnectedVerse(0);
    const auto verse3 = station->GetConnectedVerse(1);
    editor.InitializeVerse(verse, "C:/Users/Ahmed Mustafa/Downloads/Video/Gen-3 Alpha Turbo 1547404312, StarPlusWallpaperpn, M 5.mp4", 5);
    editor.InitializeVerse(verse2, "C:/Users/Ahmed Mustafa/Downloads/Video/6973-197914400_medium.mp4", 6);
    editor.InitializeVerse(verse3, "C:/Users/Ahmed Mustafa/Downloads/Video/Vanish.mp4", 24);

    float printTimer = 0.0f; // Timer to track printing interval

    // SPI::StationNetworkSerializer serializer(&app);
    //
    // serializer.ExportSpiFile("test.spi");
    //
    // const auto buffer = serializer.ExportSpiBuffer();
    //
    // for (const auto& byte : buffer) {
    //     std::cout << byte << " ";
    // }

    // serializer.ImportSpiFile("test.spi");

    app.Play();

    while (true) {
        static clock_t lastTime = std::clock();
        const clock_t now = std::clock();
        const float deltaTime = static_cast<float>(now - lastTime) / CLOCKS_PER_SEC;
        lastTime = now;

        app.OnUpdate(deltaTime);

        printTimer += deltaTime;

        if (printTimer >= 1.0f) {
            std::cout << "Delta Time: " << deltaTime << "  seconds" << std::endl;
            std::cout << "Current Time: " << app.GetCurrentTime() << " seconds" << "\t\r" << std::flush << std::endl;
            printTimer = 0.0f;
        }

        for (const auto clips = app.DataToBind(); const auto& clip : clips) {
            if (!clip) continue;
            auto videoClip = std::dynamic_pointer_cast<SPI::VideoClip>(clip);
            std:: cout << "Clip: " << videoClip->mediaPath << " - " << videoClip->start << " to " << videoClip->end << std::endl;
        }

        if (app.GetCurrentState() == SPI::EngineState::STATIONED_PAUSE) {

            if (const auto channelData = app.GetStationChannel()->Receive()) {
                std::cout << *std::dynamic_pointer_cast<SPI::McqChannelSchema>(channelData) << std::endl;
            }

            int thread;
            std::cin >> thread;
            app.Travel(thread);
            app.Rewind();
            app.Play();
        }
    }

    return 0;
}
