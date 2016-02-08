#include "ModelLoader.h"

void ModelLoader::DoStuff()
{
	const aiScene* scene = aiImportFile("test.dae", aiProcessPreset_TargetRealtime_MaxQuality);
}