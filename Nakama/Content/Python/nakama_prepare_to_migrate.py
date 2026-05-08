"""
Copyright 2025 The Nakama Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

import unreal
import sys

PACKAGE_PATH = "/Game"

def replace_nakama_nodes(package_path=PACKAGE_PATH):
    unreal.log(f"Searching for Nakama nodes under: {package_path}")

    assets = unreal.AssetRegistryHelpers.get_asset_registry().get_assets(
        unreal.ARFilter(
            class_names=["Blueprint", "WidgetBlueprint"],
            recursive_paths=True,
            package_paths=[package_path]
        )
    )

    if not assets:
        unreal.log_warning("No blueprints found.")
        return

    unreal.log(f"Found {len(assets)} blueprint(s). Processing...")

    total = 0
    with unreal.ScopedSlowTask(len(assets), "Replacing Nakama nodes...") as task:
        task.make_dialog(True)

        for asset in assets:
            if task.should_cancel():
                unreal.log_warning("Cancelled by user.")
                break

            task.enter_progress_frame(1, f"Processing {asset.asset_name}...")

            bp = unreal.EditorAssetLibrary.load_asset(str(asset.package_name))
            if not bp:
                continue

            count = unreal.NakamaBpMigrationUtil.replace_latent_nakama_nodes_with_comments(bp)
            if count > 0:
                unreal.log(f"  Replaced {count} node(s) in {bp.get_name()}")
                unreal.EditorAssetLibrary.save_asset(bp.get_path_name())
                total += count

    unreal.log(f"Done. Total nodes replaced: {total}")

path = sys.argv[1] if len(sys.argv) > 1 else PACKAGE_PATH
replace_nakama_nodes(path)