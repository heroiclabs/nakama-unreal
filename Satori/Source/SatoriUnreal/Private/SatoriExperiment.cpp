#include "SatoriExperiment.h"
#include "NakamaUtils.h"

FSatoriExperiment::FSatoriExperiment(const FString& JsonString) : FSatoriExperiment(FNakamaUtils::DeserializeJsonObject(JsonString)) {
}

FSatoriExperiment::FSatoriExperiment(const TSharedPtr<FJsonObject> JsonObject)
{
	if (JsonObject.IsValid())
	{
		JsonObject->TryGetStringField(TEXT("name"), Name);
		JsonObject->TryGetStringField(TEXT("value"), Value);
	}
}

FSatoriExperiment::FSatoriExperiment()
{
}

FSatoriExperimentList::FSatoriExperimentList(const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>* ExperimentsJsonArray;
		if (JsonObject->TryGetArrayField(TEXT("experiments"), ExperimentsJsonArray))
		{
			for (const TSharedPtr<FJsonValue>& ExperimentJsonValue : *ExperimentsJsonArray)
			{
				if (TSharedPtr<FJsonObject> ExperimentJsonObject = ExperimentJsonValue->AsObject())
				{
					FSatoriExperiment Experiment(ExperimentJsonObject);
					if (!Experiment.Name.IsEmpty())
					{
						Experiments.Add(Experiment);
					}
				}
			}
		}
	}
}

FSatoriExperimentList::FSatoriExperimentList()
{
}
