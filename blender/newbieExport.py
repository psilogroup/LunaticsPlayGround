import bpy
import bmesh

def export_vector(vector,file):
    file.write("<Vec>\n")
    file.write("%f\n" % vector[0])
    file.write("%f\n" % vector[1])
    file.write("%f\n" % vector[2])
    file.write("</Vec>\n")

def export_vector4(vector,file):
    file.write("<Vec4>\n")
    file.write("%f\n" % vector[0])
    file.write("%f\n" % vector[1])
    file.write("%f\n" % vector[2])
    file.write("1.0\n")
    file.write("</Vec4>\n")
    
    
def export_vector_position(vector,file):
    file.write("<Pos>\n")
    export_vector(vector,file)
    file.write("</Pos>\n")

def export_vector_size(vector,file):
    file.write("<Size>\n")
    export_vector(vector,file)
    file.write("</Size>\n")

def export_vector_rotation(vector,file):
    file.write("<Rot>\n")
    export_vector(vector,file)
    file.write("</Rot>\n")
    
def export_material(material,file):
    file.write("<Mat>\n")
    file.write("<Kd>\n")
    export_vector4(material.diffuse_color,file)
    file.write("</Kd>\n")
    file.write("<Ks>\n")
    export_vector4(material.specular_color,file)
    file.write("</Ks>\n")
    file.write("<Ka>\n")
    export_vector4(material.diffuse_color,file)
    file.write("</Ka>\n")
    file.write("</Mat>\n")

def export_mesh_data(mesh,file):
    
    me = mesh.data
    bm = bmesh.new()
    bm.from_mesh(me)
    bmesh.ops.triangulate(bm, faces=bm.faces)   
    bm.to_mesh(me)
    bm.free()
    faceuv = len(me.uv_textures) > 0
    
    file.write("<IndexData>\n")  
    for face in me.polygons:
        for vert in face.vertices:
            file.write("%d\n" % vert)
    
    file.write("</IndexData>\n")
    file.write("<VertexeData>\n")  
    
    for vert in me.vertices:
        file.write("%f %f %f\n" % (vert.co[0], vert.co.y, vert.co.z))
    
    file.write("</VertexeData>\n")           
    if faceuv:
        uv_texture = me.uv_textures.active.data
        uv_layer = me.uv_layers.active.data
        file.write("<UVData>\n")
        for poly in me.polygons:
            # range is used here to show how the polygons reference loops,
            # for convenience 'poly.loop_indices' can be used instead.
            for loop_index in range(poly.loop_start, poly.loop_start + poly.loop_total):
                file.write("%f %f\n" % (uv_layer[loop_index].uv[0],uv_layer[loop_index].uv[0]))
            
        file.write("</UVData>\n")
    
def export_cube(cubeData,file):
    file.write("<Cube>\n")
    file.write("<Name>\n")
    file.write("%s\n" % cubeData.name)
    file.write("<Name>\n")
    export_vector_position(cubeData.location,file)
    export_vector_size(cubeData.dimensions,file)
    export_vector_rotation(cubeData.rotation_euler,file)
    export_material(cubeData.active_material,file)
    if (cubeData.rigid_body is None) is False:        
        file.write("<Mass>\n")
        file.write("%s\n" % cubeData.rigid_body.mass)
        file.write("</Mass>\n")
        file.write("<Type>\n")
        file.write("1\n")
        file.write("</Type>\n")
    else:
        file.write("<Mass>\n")
        file.write("0\n")
        file.write("</Mass>\n")
        file.write("<Type>\n")
        file.write("0\n")
        file.write("</Type>\n")
           
    export_mesh_data(cubeData,file)
    file.write("</Cube>\n")

    

def write_some_data(context, filepath, use_some_setting):
    f = open(filepath, 'w', encoding='utf-8')
    for x in bpy.data.scenes['Scene'].objects:
            if "Cube" in x.name:
                export_cube(x,f)
                
    f.close()

    return {'FINISHED'}


# ExportHelper is a helper class, defines filename and
# invoke() function which calls the file selector.
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator


class ExportSomeData(Operator, ExportHelper):
    """This appears in the tooltip of the operator and in the generated docs"""
    bl_idname = "export_test.some_data"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "Export Some Data"

    # ExportHelper mixin class uses this
    filename_ext = ".xml"

    filter_glob = StringProperty(
            default="*.xml",
            options={'HIDDEN'},
            )

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.
    use_setting = BoolProperty(
            name="Example Boolean",
            description="Example Tooltip",
            default=True,
            )

    type = EnumProperty(
            name="Example Enum",
            description="Choose between two items",
            items=(('OPT_A', "First Option", "Description one"),
                   ('OPT_B', "Second Option", "Description two")),
            default='OPT_A',
            )

    def execute(self, context):
        return write_some_data(context, self.filepath, self.use_setting)


# Only needed if you want to add into a dynamic menu
def menu_func_export(self, context):
    self.layout.operator(ExportSomeData.bl_idname, text="Text Export Operator")


def register():
    bpy.utils.register_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportSomeData)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


if __name__ == "__main__":
    register()

    # test call
    bpy.ops.export_test.some_data('INVOKE_DEFAULT')
