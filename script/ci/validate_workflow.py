#!/usr/bin/env python3
"""
验证 GitHub Actions workflow 语法
"""

import yaml
import sys
from pathlib import Path


def validate_workflow(file_path: str):
    """验证 workflow 文件"""
    try:
        with open(file_path) as f:
            workflow = yaml.safe_load(f)
        
        print(f"✓ Valid YAML: {file_path}")
        
        # 检查必需字段（注意：YAML 'on' 会被解析为 True）
        if 'name' not in workflow:
            print("  ⚠ Warning: Missing 'name' field")
        
        # GitHub Actions uses 'on' key which becomes True in Python
        triggers = workflow.get('on') or workflow.get(True)
        if not triggers:
            print("  ✗ Error: Missing 'on' trigger")
            return False
        
        if 'jobs' not in workflow:
            print("  ✗ Error: Missing 'jobs' section")
            return False
        
        # 检查每个 job
        for job_name, job_config in workflow['jobs'].items():
            print(f"  Job: {job_name}")
            
            if 'runs-on' not in job_config:
                print(f"    ✗ Missing 'runs-on' for job {job_name}")
            
            if 'steps' not in job_config:
                print(f"    ✗ Missing 'steps' for job {job_name}")
            else:
                for i, step in enumerate(job_config['steps']):
                    if 'run' not in step and 'uses' not in step:
                        print(f"    ⚠ Step {i+1} has no 'run' or 'uses'")
        
        print(f"✓ Workflow looks valid")
        return True
        
    except yaml.YAMLError as e:
        print(f"✗ Invalid YAML in {file_path}: {e}")
        return False
    except Exception as e:
        print(f"✗ Error validating {file_path}: {e}")
        return False


def main():
    workflows_dir = Path(".github/workflows")
    
    if not workflows_dir.exists():
        print("No .github/workflows directory found")
        sys.exit(1)
    
    all_valid = True
    for workflow_file in workflows_dir.glob("*.yml"):
        if not validate_workflow(str(workflow_file)):
            all_valid = False
        print()
    
    sys.exit(0 if all_valid else 1)


if __name__ == "__main__":
    main()
