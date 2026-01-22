# ActionRougelike

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.6-blue?logo=unrealengine)
![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus)
![License](https://img.shields.io/badge/License-MIT-green)

> A C++ action roguelike game built in Unreal Engine 5.6

---

## 🎮 Features

| Feature | Description |
|---------|-------------|
| **Character System** | Third-person character with double jump and air redirection |
| **Combat** | Magic projectile attacks with animation montages |
| **VFX** | Niagara particle effects for casting and explosions |
| **Physics** | Interactive environment with physics-enabled objects |
| **Input** | UE5 Enhanced Input System |

---

## 🏗️ Project Structure

```
ActionRougelike/
│
├── 📁 Source/ActionRougelike/
│   ├── 🎭 RougeCharacter          ← Player character
│   ├── 📁 Projectiles/
│   │   └── 🔮 RougeProjectileMagic ← Magic projectile system
│   └── 📁 Objects/
│       └── 💥 RougeExplosiveBarrel ← Explosive environment object
│
├── 📁 Content/ActionRougeLike/
│   ├── 📁 Blueprints/             ← Blueprint assets
│   ├── 📁 VFX/                    ← Niagara effects
│   └── 📁 Maps/                   ← Game levels
│
└── 📁 Config/                     ← Engine & input settings
```

---

## 🔧 Tech Stack

```
┌─────────────────────────────────────────────┐
│  Unreal Engine 5.6                          │
├─────────────────────────────────────────────┤
│  Enhanced Input System    │  Niagara VFX    │
│  Gameplay Ability System  │  Physics Engine │
└─────────────────────────────────────────────┘
```

**Dependencies:**
- `EnhancedInput` - Modern input handling
- `Niagara` - Visual effects

---

## 🚀 Getting Started

1. **Clone** the repository
2. **Open** `ActionRougelike.uproject` with Unreal Engine 5.6
3. **Build** via Visual Studio or Rider
4. **Play** in editor (PIE)

---

## 📸 Screenshots

<!-- Add screenshots here -->
*Coming soon...*

---

## 📝 License

MIT License - See [LICENSE](LICENSE) for details
