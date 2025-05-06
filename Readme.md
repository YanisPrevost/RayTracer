# RayTracer

## 📝 Description

RayTracer est un moteur de rendu 3D basé sur la technique du lancer de rayons. Cette technique simule le comportement de la lumière en traçant des rayons depuis la caméra à travers chaque pixel de l'écran virtuel jusque dans la scène 3D, permettant ainsi de créer des images réalistes avec des effets d'ombrage, de réflexion et de réfraction.

## 🌟 Fonctionnalités

- **Rendu de primitives 3D** : Sphères, Cylindres, Cônes, Plans
- **Système d'éclairage** : Sources de lumière directionnelles et ponctuelles
- **Chargement dynamique** : Plugins pour ajouter facilement de nouvelles primitives et sources de lumière
- **Configuration flexible** : Descriptions de scènes personnalisables via des fichiers de configuration

## 🖼️ Exemples de rendu

<div style="display: flex; justify-content: space-between; flex-wrap: wrap;">
  <div style="text-align: center; flex: 1; min-width: 200px; margin: 10px;">
    <h3>Scène "Cow"</h3>
    <img src="Images/cow.png" alt="Rendu: Vache" style="max-width: 100%; height: auto;">
  </div>
  <div style="text-align: center; flex: 1; min-width: 200px; margin: 10px;">
    <h3>Scène "Forêt"</h3>
    <img src="Images/foret.png" alt="Rendu: Forêt" style="max-width: 100%; height: auto;">
  </div>
  <div style="text-align: center; flex: 1; min-width: 200px; margin: 10px;">
    <h3>Scène "Spirale"</h3>
    <img src="Images/spiral.png" alt="Rendu: Spirale" style="max-width: 100%; height: auto;">
  </div>
  <div style="text-align: center; flex: 1; min-width: 200px; margin: 10px;">
    <h3>Scène "Spirale"</h3>
    <img src="Images/saturn.png" alt="Rendu: Saturne" style="max-width: 100%; height: auto;">
  </div>
</div>

## 🛠️ Installation

```bash
# Cloner le dépôt
git clone [url-du-depot]
cd RayTracer

# Construire le projet
chmod +x build.sh
./build.sh
```

## 🚀 Utilisation

```bash
# Exécuter le ray tracer avec un fichier de configuration
./raytracer Config/basic.cfg

# Autres exemples de configuration
./raytracer Config/cow.cfg
./raytracer Config/foret.cfg
./raytracer Config/spirale.cfg
```

## 📋 Format des fichiers de configuration

Les fichiers de configuration (.cfg) permettent de décrire la scène à rendre, incluant:

```
camera = {
    fieldOfView = 90.0;
    position = { x = 2.0; y = 5.0; z = 10.0; };
    rotation = { x = 0; y = 0; z = -1; };
    resolution = { width = 1280; height = 720; };
};

primitives = {
    spheres = (
        { x = 0.0; y = 0.0; z = 0.0; r = 1.0; color = { r = 255; g = 0; b = 0; }; }
    );
    # Autres primitives...
};

lights = {
    point = (
        {
            position = { x = 0.0; y = 30.0; z = 40.0; };
            intensity = 0.7;
            color = { r = 255; g = 255; b = 255; };
        }
    );
};
```

## 🧩 Architecture du projet

Le projet est organisé selon une architecture modulaire:

- **Core**: Moteur principal du ray tracer
- **Primitives**: Formes géométriques rendues (Sphère, Plan, etc.)
- **Lumières**: Sources d'éclairage (Directionnelle, Ponctuelle)
- **Parsing**: Analyse des fichiers de configuration
- **Visualisation**: Sortie des images au format PPM

## 👥 Contributeurs
- Yanis Prevost, Raphaël Grissonnanche, Anthony Colombani-Gailleur, Maxime Finaud
