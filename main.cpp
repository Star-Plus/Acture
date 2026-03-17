#include <Features/MCQStation.h>

#include "Application.h"
#include "Core/LeafStation.h"
#include "Editor/Editor.h"
#include "Schemas/McqChannelSchema.h"
#include "Serializers/StationNetworkSerializer.h"
#include "Triggers/Features/DirectCall/DirectCallTrigger.h"
#include "Units/VideoClip.h"

int main() {
    SPI::Application app;
    const SPI::Editor editor(app);

    const auto root = app.GetStationNetwork()->GetRoot();

    const auto id = editor.AddStation(0, SPI::STATION_TYPE::MCQ, 3.0);
    const auto station = std::dynamic_pointer_cast<SPI::MCQStation>(app.GetStationNetwork()->GetStationById(id));

    const auto directTrigger = new SPI::DirectCallTrigger(&app);

    station->SetTrigger(directTrigger);

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

    editor.InitializeVerse(verse, "1", 5);
    editor.InitializeVerse(verse2, "2", 6);
    editor.InitializeVerse(verse3, "3", 24);

    verse->tracks[0]->clips[0]->externalRef = "https://www.youtube.com/watch?v=YV8mPZ22xVM";
    verse2->tracks[0]->clips[0]->externalRef = "https://www.youtube.com/watch?v=iZpMnTQb_ew";
    verse3->tracks[0]->clips[0]->externalRef = "https://www.youtube.com/watch?v=8wo5ayPjAVE";

    SPI::StationNetworkSerializer serializer(&app);
    serializer.SetAssetMode(SPI::ASSETS_MODE::EXTERNAL_REF);

    serializer.ExportSpiFile("test.spi");
    serializer.ImportSpiFile("test.spi");

    std::cout << app.GetStationNetwork()->Size() << std::endl;

    const auto r = app.GetStationNetwork()->GetRoot();

    std::cout << std::dynamic_pointer_cast<SPI::VideoClip>(r->GetConnectedVerse(0)->tracks[0]->clips[0])->mediaPath << std::endl;
    std::cout << std::dynamic_pointer_cast<SPI::VideoClip>(app.GetStationNetwork()->GetStationById(r->GetConnectedStation(0))->GetConnectedVerse(0)->tracks[0]->clips[0])->mediaPath << std::endl;

    app.Play();

    app.OnUpdate();

    const auto channelData = app.ReceiveChannelData();
    std::cout << *std::dynamic_pointer_cast<SPI::McqChannelSchema>(channelData) << std::endl;
    std::cout << *std::dynamic_pointer_cast<SPI::McqChannelSchema>(channelData) << std::endl;


    return 0;
}

