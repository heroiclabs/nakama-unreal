/*
* Copyright 2025 The Nakama Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NakamaBpMigrationUtil.h"

#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraphNode_Comment.h"
#include "K2Node_AsyncAction.h"
#include "Engine/Blueprint.h"
#include "K2Node_BaseAsyncTask.h"
#include "Kismet2/KismetEditorUtilities.h"

bool UNakamaBpMigrationUtil::IsLatentNakamaNode(UEdGraphNode* Node)
{
    if (!Node) return false;

    if (const UK2Node_AsyncAction* AsyncAction = Cast<UK2Node_AsyncAction>(Node))
    {
        const FString ClassName = AsyncAction->GetFactoryFunction()->GetOuterUClass()->GetName();

        return ClassName.Contains(TEXT("Nakama"), ESearchCase::IgnoreCase) || ClassName.Contains(TEXT("Satori"), ESearchCase::IgnoreCase);
    }

    return false;
}

int32 UNakamaBpMigrationUtil::ReplaceLatentNakamaNodesWithComments(UBlueprint* Blueprint)
{
    if (!Blueprint) return 0;

    TArray<UEdGraph*> AllGraphs;
    Blueprint->GetAllGraphs(AllGraphs);

    int32 ReplacedCount = 0;

    for (UEdGraph* Graph : AllGraphs)
    {
        if (!Graph) continue;

        TArray<UEdGraphNode*> ToReplace;
        for (UEdGraphNode* Node : Graph->Nodes)
        {
            if (IsLatentNakamaNode(Node))
                ToReplace.Add(Node);
        }

        for (UEdGraphNode* Node : ToReplace)
        {
            const int32 NodeX = Node->NodePosX;
            const int32 NodeY = Node->NodePosY;
            const FString OldTitle = Node->GetNodeTitle(ENodeTitleType::FullTitle).ToString();

            Node->BreakAllNodeLinks();
            Graph->RemoveNode(Node);

            UEdGraphNode_Comment* Comment = NewObject<UEdGraphNode_Comment>(Graph);
            Comment->NodePosX = NodeX;
            Comment->NodePosY = NodeY;
            Comment->NodeWidth = 300;
            Comment->NodeHeight = 200;
            Comment->bCommentBubblePinned = 0;
            Comment->bCommentBubbleVisible_InDetailsPanel = false;
            Comment->CommentColor = FColor(255, 0, 0, 255);
            Comment->NodeComment = FString::Printf(
                TEXT("NAKAMA MIGRATE: Node '%s' was removed. Replace after upgrading SDK."), *OldTitle);

            Graph->AddNode(Comment, false, false);
            ReplacedCount++;
        }
    }

    if (ReplacedCount > 0)
    {
        if (const bool bSuccess = Blueprint->MarkPackageDirty(); bSuccess)
            FKismetEditorUtilities::CompileBlueprint(Blueprint);
    }

    return ReplacedCount;
}