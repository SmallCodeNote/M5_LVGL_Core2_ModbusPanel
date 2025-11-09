using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

using WinFormStringCnvClass;

namespace TextReplaceCopy
{
    public partial class Form1 : Form
    {
        string thisExeDirPath;

        public Form1()
        {
            InitializeComponent();
            thisExeDirPath = Path.GetDirectoryName(Application.ExecutablePath);
        }

        private void button_Copy_Click(object sender, EventArgs e)
        {
            try
            {
                string srcDir = textBox_SrcPath.Text.Trim();
                string dstDir = textBox_TargetPath.Text.Trim();

                if (string.IsNullOrWhiteSpace(srcDir) || string.IsNullOrWhiteSpace(dstDir))
                {
                    return;
                }

                if (!Directory.Exists(srcDir))
                {
                    return;
                }

                if (!Directory.Exists(dstDir))
                {
                    Directory.CreateDirectory(dstDir);
                }

                var replaceDict = new Dictionary<string, string>();
                var lines = textBox_ReplaceList.Lines;
                foreach (var line in lines)
                {
                    var parts = line.Split('\t');
                    if (parts.Length == 2)
                    {
                        replaceDict[parts[0]] = parts[1];
                    }
                }

                string[] extensions = { ".c", ".cpp", ".h", ".hpp" };

                var files = Directory.GetFiles(srcDir, "*.*", SearchOption.AllDirectories)
                                     .Where(f => extensions.Contains(Path.GetExtension(f).ToLower()))
                                     .ToList();

                foreach (var srcFilePath in files)
                {
                    string relativePath = srcFilePath.Substring(srcDir.Length).TrimStart(Path.DirectorySeparatorChar);
                    string dstFilePath = Path.Combine(dstDir, relativePath);

                    string dstFileDir = Path.GetDirectoryName(dstFilePath);
                    if (!Directory.Exists(dstFileDir))
                    {
                        Directory.CreateDirectory(dstFileDir);
                    }

                    File.Copy(srcFilePath, dstFilePath, true);

                    string content = File.ReadAllText(dstFilePath, Encoding.UTF8);

                    foreach (var kvp in replaceDict)
                    {
                        content = content.Replace(kvp.Key, kvp.Value);
                    }

                    File.WriteAllText(dstFilePath, content, Encoding.UTF8);
                }

            }
            catch (Exception ex)
            {
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "TEXT|*.txt";
            if (false && ofd.ShowDialog() == DialogResult.OK)
            {
                WinFormStringCnv.setControlFromString(this, File.ReadAllText(ofd.FileName));
            }
            else
            {
                string paramFilename = Path.Combine(thisExeDirPath, "_param.txt");
                if (File.Exists(paramFilename))
                {
                    WinFormStringCnv.setControlFromString(this, File.ReadAllText(paramFilename));
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            string FormContents = WinFormStringCnv.ToString(this);

            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "TEXT|*.txt";

            if (false && sfd.ShowDialog() == DialogResult.OK)
            {

                File.WriteAllText(sfd.FileName, FormContents);
            }
            else
            {
                string paramFilename = Path.Combine(thisExeDirPath, "_param.txt");
                File.WriteAllText(paramFilename, FormContents);
            }
        }

        private void button_SendClipboard_VarCode_Click(object sender, EventArgs e)
        {
            string dirPath = textBox_SrcPath.Text.Trim();
            string headerPath = Path.Combine(dirPath, "vars.h");

            if (!File.Exists(headerPath))
            {
                MessageBox.Show("vars.h not exist");
                return;
            }

            string[] lines = File.ReadAllLines(headerPath);
            StringBuilder sb = new StringBuilder();

            foreach (string line in lines)
            {
                string trimmed = line.Trim();

                // extern int32_t get_var_xxx();
                Match mInt = Regex.Match(trimmed, @"extern\s+int32_t\s+(\w+)\s*\(\s*\);");
                if (mInt.Success)
                {
                    string func = mInt.Groups[1].Value;
                    string varName = func.Replace("get_var_", "");
                    sb.AppendLine($"int32_t {varName}; extern \"C\" int32_t {func}() {{ return {varName}; }}");
                    continue;
                }

                // extern float get_var_xxx();
                Match mFloat = Regex.Match(trimmed, @"extern\s+float\s+(\w+)\s*\(\s*\);");
                if (mFloat.Success)
                {
                    string func = mFloat.Groups[1].Value;
                    string varName = func.Replace("get_var_", "");
                    sb.AppendLine($"float {varName}; extern \"C\" float {func}() {{ return {varName}; }}");
                    continue;
                }

                // extern bool get_var_xxx();
                Match mBool = Regex.Match(trimmed, @"extern\s+bool\s+(\w+)\s*\(\s*\);");
                if (mBool.Success)
                {
                    string func = mBool.Groups[1].Value;
                    string varName = func.Replace("get_var_", "");
                    sb.AppendLine($"bool {varName}; extern \"C\" bool {func}() {{ return {varName}; }}");
                    continue;
                }

                // extern const char *get_var_xxx();
                Match mStr = Regex.Match(trimmed, @"extern\s+const\s+char\s*\*\s*(\w+)\s*\(\s*\);");
                if (mStr.Success)
                {
                    string func = mStr.Groups[1].Value;
                    string varName = func.Replace("get_var_", "");
                    sb.AppendLine($"std::string {varName}; extern \"C\" const char *{func}() {{ return {varName}.c_str(); }}");
                    continue;
                }

                // extern void set_var_xxx(int32_t value);
                Match mSetInt = Regex.Match(trimmed, @"extern\s+void\s+(set_var_\w+)\s*\(\s*int32_t\s+(\w+)\s*\);");
                if (mSetInt.Success)
                {
                    string func = mSetInt.Groups[1].Value;
                    string param = mSetInt.Groups[2].Value;
                    string varName = func.Replace("set_var_", "");
                    sb.AppendLine($"extern \"C\" void {func}(int32_t {param}) {{ {varName} = {param}; }}");
                    sb.AppendLine("");
                    continue;
                }

                // extern void set_var_xxx(float value);
                Match mSetFloat = Regex.Match(trimmed, @"extern\s+void\s+(set_var_\w+)\s*\(\s*float\s+(\w+)\s*\);");
                if (mSetFloat.Success)
                {
                    string func = mSetFloat.Groups[1].Value;
                    string param = mSetFloat.Groups[2].Value;
                    string varName = func.Replace("set_var_", "");
                    sb.AppendLine($"extern \"C\" void {func}(float {param}) {{ {varName} = {param}; }}");
                    sb.AppendLine("");
                    continue;
                }

                // extern void set_var_xxx(const char *value);
                Match mSetStr = Regex.Match(trimmed, @"extern\s+void\s+(set_var_\w+)\s*\(\s*const\s+char\s*\*\s*(\w+)\s*\);");
                if (mSetStr.Success)
                {
                    string func = mSetStr.Groups[1].Value;
                    string param = mSetStr.Groups[2].Value;
                    string varName = func.Replace("set_var_", "");
                    sb.AppendLine($"extern \"C\" void {func}(const char *{param}) {{ {varName} = {param}; }}");
                    sb.AppendLine("");
                    continue;
                }

                // extern void set_var_xxx(bool value);
                Match mSetBool = Regex.Match(trimmed, @"extern\s+void\s+(set_var_\w+)\s*\(\s*bool\s+(\w+)\s*\);");
                if (mSetBool.Success)
                {
                    string func = mSetBool.Groups[1].Value;
                    string param = mSetBool.Groups[2].Value;
                    string varName = func.Replace("set_var_", "");
                    sb.AppendLine($"extern \"C\" void {func}(bool {param}) {{ {varName} = {param}; }}");
                    sb.AppendLine("");
                    continue;
                }
            }

            
            Clipboard.SetText(sb.ToString());
        }

        private void button_SendClipboard_ActionCode_Click(object sender, EventArgs e)
        {
            string srcDir = textBox_SrcPath.Text.Trim();
            string targetDir = textBox_TargetPath.Text.Trim();

            string headerPath = Path.Combine(srcDir, "actions.h");
            string cppPath = Path.Combine(Directory.GetParent(targetDir).FullName, "actions.cpp");

            if (!File.Exists(headerPath))
            {
                MessageBox.Show("actions.h is not found");
                return;
            }

            if (!File.Exists(cppPath))
            {
                MessageBox.Show("actions.cpp is not found");
                return;
            }

            string[] headerLines = File.ReadAllLines(headerPath);
            string cppContent = File.ReadAllText(cppPath);

            StringBuilder sb = new StringBuilder();

            foreach (string line in headerLines)
            {
                string trimmed = line.Trim();

                // extern void action_xxx(lv_event_t * e);
                Match m = Regex.Match(trimmed, @"extern\s+void\s+(action_\w+)\s*\(\s*lv_event_t\s*\*\s*\w+\s*\);");
                if (m.Success)
                {
                    string funcName = m.Groups[1].Value;

                    // cpp check
                    string pattern = $@"extern\s+""C""\s+void\s+{Regex.Escape(funcName)}\s*\(\s*lv_event_t\s*\*\s*\w+\s*\)";
                    if (!Regex.IsMatch(cppContent, pattern))
                    {
                        sb.AppendLine($"extern \"C\" void {funcName}(lv_event_t *e)");
                        sb.AppendLine($"{{");
                        sb.AppendLine($"");
                        sb.AppendLine($"");
                        sb.AppendLine($"}}");
                    }
                }
            }

            if (sb.Length > 0)
            {
                Clipboard.SetText(sb.ToString());
            }
            else
            {
                MessageBox.Show("found no function");
            }

        }
    }
}
