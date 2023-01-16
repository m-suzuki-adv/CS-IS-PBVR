#  DON'T EDIT THIS FILE.

OBJECTS := \
$(OUTDIR)/PBVRFileInformation/UnstructuredPfi.o \
$(OUTDIR)/Exporter/VtkExport.o \
$(OUTDIR)/Exporter/UnstructuredVolumeObjectExporter.o \
$(OUTDIR)/Exporter/StructuredVolumeObjectExporter.o \
$(OUTDIR)/FileFormat/VtkCompositeDataSetFileFormat.o \
$(OUTDIR)/Importer/VtkImport.o \
$(OUTDIR)/TimeSeriesFiles/AVS/AvsField.o


$(OUTDIR)/PBVRFileInformation/%.o: ./PBVRFileInformation/%.cpp ./PBVRFileInformation/%.h
	$(MKDIR) $(OUTDIR)/PBVRFileInformation
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/Exporter/%.o: ./Exporter/%.cpp ./Exporter/%.h
	$(MKDIR) $(OUTDIR)/Exporter
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/FileFormat/%.o: ./FileFormat/%.cpp ./FileFormat/%.h
	$(MKDIR) $(OUTDIR)/FileFormat
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/Importer/%.o: ./Importer/%.cpp ./Importer/%.h
	$(MKDIR) $(OUTDIR)/Importer
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/TimeSeriesFiles/AVS/%.o: ./TimeSeriesFiles/AVS/%.cpp ./TimeSeriesFiles/AVS/%.h
	$(MKDIR) $(OUTDIR)/TimeSeriesFiles
	$(MKDIR) $(OUTDIR)/TimeSeriesFiles/AVS
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<

$(OUTDIR)/./%.o: ./%.cpp ./%.h
	$(MKDIR) $(OUTDIR)
	$(CPP) -c $(CPPFLAGS) $(DEFINITIONS) $(INCLUDE_PATH) -o $@ $<


install::
	$(MKDIR) $(INSTALL_DIR)/include/
	$(INSTALL) ./*.h $(INSTALL_DIR)/include
	$(MKDIR) $(INSTALL_DIR)/include/Exporter
	$(INSTALL) ./Exporter/*.h $(INSTALL_DIR)/include/Exporter
# FileFormat
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat
	$(INSTALL) ./FileFormat/*.h $(INSTALL_DIR)/include/FileFormat
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat/AVS
	$(INSTALL) ./FileFormat/AVS/*.h $(INSTALL_DIR)/include/FileFormat/AVS
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat/CGNS
	$(INSTALL) ./FileFormat/CGNS/*.h $(INSTALL_DIR)/include/FileFormat/CGNS
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat/KVSML
	$(INSTALL) ./FileFormat/KVSML/*.h $(INSTALL_DIR)/include/FileFormat/KVSML
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat/PLOT3D
	$(INSTALL) ./FileFormat/PLOT3D/*.h $(INSTALL_DIR)/include/FileFormat/PLOT3D
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat/STL
	$(INSTALL) ./FileFormat/STL/*.h $(INSTALL_DIR)/include/FileFormat/STL
	$(MKDIR) $(INSTALL_DIR)/include/FileFormat/VTK
	$(INSTALL) ./FileFormat/VTK/*.h $(INSTALL_DIR)/include/FileFormat/VTK
#
	$(MKDIR) $(INSTALL_DIR)/include/Importer
	$(INSTALL) ./Importer/*.h $(INSTALL_DIR)/include/Importer
	$(MKDIR) $(INSTALL_DIR)/include/PBVRFileInformation
	$(INSTALL) ./PBVRFileInformation/*.h $(INSTALL_DIR)/include/PBVRFileInformation
	$(MKDIR) $(INSTALL_DIR)/include/TimeSeriesFiles
	$(INSTALL) ./TimeSeriesFiles/*.h $(INSTALL_DIR)/include/TimeSeriesFiles
	$(MKDIR) $(INSTALL_DIR)/include/TimeSeriesFiles/EnSight
	$(INSTALL) ./TimeSeriesFiles/EnSight/*.h $(INSTALL_DIR)/include/TimeSeriesFiles/EnSight
	$(MKDIR) $(INSTALL_DIR)/include/TimeSeriesFiles/AVS
	$(INSTALL) ./TimeSeriesFiles/AVS/*.h $(INSTALL_DIR)/include/TimeSeriesFiles/AVS
