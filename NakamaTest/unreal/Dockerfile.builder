FROM ue4-source

COPY --chown=ue4:ue4 . /tmp/project
SHELL ["/bin/bash", "-c"]

RUN source /home/ue4/UnrealEngine/Engine/Build/BatchFiles/Linux/SetupMono.sh /home/ue4/UnrealEngine/Engine/Build/BatchFiles/Linux && \
    mono /home/ue4/UnrealEngine/Engine/Binaries/DotNET/UnrealBuildTool.exe -Project=/tmp/project/NakamaTestApp.uproject \
    NakamaTest Linux Debug

ENTRYPOINT [ "/tmp/project/Binaries/Linux/NakamaTest-Linux-Debug" ]
