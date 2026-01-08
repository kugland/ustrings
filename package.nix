{
  pkgs ? import <nixpkgs> {},
  lib ? pkgs.lib,
}:
pkgs.stdenv.mkDerivation {
  pname = "ustrings";
  version = "1.0.0";
  src = lib.cleanSourceWith {
    src = ./.;
    filter = path: type: let
      baseName = baseNameOf path;
    in
      baseName == "ustrings.c" || baseName == "CMakeLists.txt" || baseName == "README.md";
  };
  nativeBuildInputs = [pkgs.cmake];
  outputs = ["out" "doc"];
  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
  ];
  postInstall = ''
    mkdir -p $doc/share/doc
    mv $out/share/doc/ustrings/README.md $doc/share/doc/README.md
    rmdir $out/share/doc/ustrings $out/share/doc $out/share
  '';
  meta = with lib; {
    description = "UTF-8 aware version of strings utility";
    homepage = "https://github.com/kugland/ustrings";
    license = licenses.mit;
    maintainers = [maintainers.kugland];
    platforms = platforms.unix;
    mainProgram = "ustrings";
  };
}
