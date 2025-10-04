Perfect — here’s a lean **Gameplan** for your first 3 backbone systems.

---

# Gameplan (First 3 Systems)

## 1. GAS Integration

**Goal:** Have the Gameplay Ability System running with 1 test ability (“Capture Tile”).
**Steps:**

1. Enable modules: `GameplayAbilities`, `GameplayTags`, `GameplayTasks` in `.uproject` + `Build.cs`.
2. Add `UAbilitySystemComponent` to **PlayerState** (multiplayer-friendly).
3. Define base `GameplayTags` in `DefaultGameplayTags.ini`:

    * `Ability.Capture`
    * `Ability.Build.City` etc.
4. Create `UBaseGameplayAbility` class.
5. Implement `UAbility_CaptureTile` (cost soldiers, change ownership).
6. Test: Press key/tap → Ability activates → logs “Tile Captured.”

**Exit:** You can call `ASC->TryActivateAbilityByTag("Ability.Capture")` and it runs.

---

## 2. CommonUI Base

**Goal:** Shared UI foundation that handles safe areas and action routing.
**Steps:**

1. Enable **CommonUI** plugin.
2. Create `UBaseScreen` (subclass of `UCommonActivatableWidget`):

    * Safe area padding.
    * `OnBackAction`, `OnConfirmAction` handlers.
3. Create `HUDManager` (Actor or Subsystem) to push/pop screens:

    * `ShowScreen(MainMenu)`
    * `ShowScreen(MatchHUD)`
    * `ShowScreen(FTUE)`
4. Create a **Style Data Asset** (fonts, colors, margins).
5. Wire 1 button (tap) → logs action through CommonUI.

**Exit:** Boot → `HUDManager` loads `MainMenuWidget` (derived from `UBaseScreen`) → button press logs action.

---

## 3. Grid + Tile System

**Goal:** Prototype tile ownership + capture rule.
**Steps:**

1. Create `FTileData` struct:

   ```cpp
   struct FTileData {
     int32 X, Y;
     ETileOwner Owner; // Neutral, NPC, Player
     int32 Defense;
     EStructureType Structure;
     int32 Value;
   };
   ```
2. Create `ATileGridManager` Actor:

    * Generates NxN grid of `FTileData`.
    * Provides `GetNeighbors(X,Y)`.
3. Capture logic:

    * SoldiersNeeded = BaseCost × (1 + Defense*0.5).
    * If paid → set Owner = NewPlayer.
4. Grid visualization: simple instanced mesh per tile (color by Owner).
5. Test: Tap a neutral tile → attempt capture → tile color changes.

**Exit:** Player can tap on tiles and expand territory with dummy soldier pool.

---

✅ Suggested Order of Work:

1. Set up **Grid + Tile System** first (need it visible).
2. Add **GAS** and make “Capture Tile” a Gameplay Ability that calls GridManager.
3. Wrap everything in **CommonUI** so input/actions flow through the same system.

---

Do you want me to also draft **C++ stub headers** for `TileGridManager`, `FTileData`, and a sample `UAbility_CaptureTile` so you can drop them in right away?
