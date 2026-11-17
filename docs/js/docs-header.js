function applyTheme(theme) {
    document.documentElement.classList.toggle("dark-mode", theme === "dark");
    document.documentElement.classList.toggle("light-mode", theme !== "dark");
}

function preferredTheme() {
    try {
        const theme = localStorage.getItem("theme");
        if (theme === "dark" || theme === "light") return theme;
    } catch {}
    return matchMedia("(prefers-color-scheme: dark)").matches ? "dark" : "light";
}

applyTheme(preferredTheme());
document.addEventListener("theme-change", event => applyTheme(event.detail.theme));
