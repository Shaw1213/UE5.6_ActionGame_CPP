# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

ActionRougelike is an Unreal Engine 5.6 C++ action roguelike game project. The codebase uses UE5's Enhanced Input System for player input and Niagara for visual effects.

## Build Commands

Build and compile from Visual Studio or via Unreal Build Tool:
```bash
# From UE5 installation directory (adjust path as needed)
UnrealBuildTool.exe ActionRougelike Win64 Development "F:\UE5 Projects\ActionRougelike\UE5.6_ActionGame_CPP\ActionRougelike.uproject"

# Generate project files
UnrealBuildTool.exe -projectfiles -project="F:\UE5 Projects\ActionRougelike\UE5.6_ActionGame_CPP\ActionRougelike.uproject" -game -engine
```

Typically, open `ActionRougelike.sln` in Visual Studio or Rider and build from the IDE.

## Module Dependencies

Defined in `Source/ActionRougelike/ActionRougelike.Build.cs`:
- **Public:** Core, CoreUObject, Engine, InputCore, EnhancedInput
- **Private:** EnhancedInput, Niagara

When adding new features that require additional modules (e.g., Slate UI, OnlineSubsystem), update the Build.cs file.

## Architecture

### Source Organization
```
Source/ActionRougelike/
├── RougeCharacter.h/cpp           # Player character with movement, camera, attacks
├── Objects/
│   └── RougeExplosiveBarrel.h/cpp # Environmental hazards
└── Projectiles/
    └── RougeProjectileMagic.h/cpp # Abstract projectile base (intended for Blueprint subclasses)
```

### Core Systems

**Character (ARougeCharacter)**
- Uses Enhanced Input System with InputAction assets
- Spring arm camera setup for third-person view
- Double jump with air redirection
- Primary attack spawns projectiles from "Muzzle_01" socket with animation montage delay

**Projectile (ARougeProjectileMagic)**
- Abstract class designed for Blueprint extension
- Uses "Projectile" collision profile (custom, defined in DefaultEngine.ini)
- Components: SphereComponent (collision), ProjectileMovementComponent, NiagaraComponent, AudioComponent
- Applies 10 damage via ApplyPointDamage on hit

### Key Patterns

**Component Setup:**
```cpp
ComponentName = CreateDefaultSubobject<UComponentType>(TEXT("ComponentName"));
ComponentName->SetupAttachment(ParentComponent);
```

**Enhanced Input Binding:**
```cpp
UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
EnhancedInput->BindAction(InputAction, ETriggerEvent::Triggered, this, &Class::Function);
```

**Property Declaration:**
```cpp
UPROPERTY(EditDefaultsOnly, Category="Combat")
TObjectPtr<UClass> ProjectileClass;
```

## Naming Conventions

- **A** prefix for Actor classes: `ARougeCharacter`, `ARougeProjectileMagic`
- **U** prefix for UObject/Component classes
- Project prefix `Rouge` for all game classes
- Use `TObjectPtr<>` for UPROPERTY pointers (UE5 convention)

## Collision

Custom "Projectile" collision profile configured to:
- Query only (no physics simulation)
- Ignore Visibility and Camera channels
- Respond to WorldDynamic object type

## Rules
- Don't modify Engine files