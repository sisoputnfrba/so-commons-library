# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'so-commons-library'
copyright = '2024, sisoputnfrba'
author = 'sisoputnfrba'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
  'breathe',
  'exhale',
]

templates_path = ['_templates']
exclude_patterns = []

language = 'en'

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

# Breathe Configuration
breathe_projects = {
  "so-commons-library": "./build/doxygen/xml/",
}
breathe_default_project = 'so-commons-library'

# Setup the exhale extension
exhale_args = {
    # These arguments are required
    "containmentFolder":     "./build/exhale",
    "rootFileName":          "library_root.rst",
    "doxygenStripFromPath":  "../src/",
    # Heavily encouraged optional argument (see docs)
    "rootFileTitle":         "Tipos Abstractos de Datos",
    "afterTitleDescription": "Esta documentación fue generada automáticamente en base al código fuente que se encuentra en `sisoputnfrba/so-commons-library <https://github.com/sisoputnfrba/so-commons-library>`_.",
    # Suggested optional arguments
    "createTreeView":        True,
    # TIP: if using the sphinx-bootstrap-theme, you need
    # "treeViewIsBootstrap": True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin":    "INPUT = ../src/commons",
    "unabridgedOrphanKinds": {"define", "function", "variable"}
}

# Tell sphinx what the primary language being documented is.
primary_domain = 'c'

# Tell sphinx what the pygments highlight language should be.
highlight_language = 'c'
