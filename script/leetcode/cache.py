#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
统一的缓存管理器
负责文件缓存的加载、保存和过期检查
"""

import json
import time
from pathlib import Path
from typing import Any, Optional, TypeVar, Callable

T = TypeVar('T')

CACHE_DIR = Path(".leetcode-cache")
CACHE_EXPIRY_SECONDS = 24 * 60 * 60  # 24 小时过期（默认过期时间）


class CacheManager:
    """统一的缓存管理器"""
    
    @staticmethod
    def get_cache_dir() -> Path:
        """获取缓存目录"""
        cache_dir = CACHE_DIR
        cache_dir.mkdir(parents=True, exist_ok=True)
        return cache_dir
    
    @staticmethod
    def get_cache_file(key: str) -> Path:
        """获取缓存文件路径"""
        return CacheManager.get_cache_dir() / f"{key}.json"
    
    @staticmethod
    def load(key: str, expiry_seconds: Optional[int] = None) -> Optional[Any]:
        """从文件加载缓存
        
        Args:
            key: 缓存键
            expiry_seconds: 过期时间（秒），如果为 None 则使用默认过期时间
        
        Returns:
            缓存的数据，如果不存在或已过期则返回 None
        """
        cache_file = CacheManager.get_cache_file(key)
        if not cache_file.exists():
            return None
        
        try:
            with open(cache_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            # 检查是否过期
            cache_time = data.get('_cache_time', 0)
            expiry = expiry_seconds if expiry_seconds is not None else CACHE_EXPIRY_SECONDS
            
            if time.time() - cache_time > expiry:
                cache_file.unlink()  # 删除过期缓存
                return None
            
            return data.get('data')
        except (json.JSONDecodeError, KeyError, IOError):
            # 缓存文件损坏，删除它
            cache_file.unlink()
            return None
    
    @staticmethod
    def get_cache_info(key: str) -> Optional[dict]:
        """获取缓存文件的元信息（时间戳、过期时间等）"""
        cache_file = CacheManager.get_cache_file(key)
        if not cache_file.exists():
            return None
        
        try:
            with open(cache_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            cache_time = data.get('_cache_time', 0)
            age = time.time() - cache_time
            expiry = CACHE_EXPIRY_SECONDS
            remaining = max(0, expiry - age)
            
            return {
                'cache_time': cache_time,
                'age_seconds': age,
                'expiry_seconds': expiry,
                'remaining_seconds': remaining,
                'is_expired': age > expiry
            }
        except (json.JSONDecodeError, KeyError, IOError):
            return None
    
    @staticmethod
    def save(key: str, data: Any) -> None:
        """保存缓存到文件"""
        cache_file = CacheManager.get_cache_file(key)
        try:
            cache_data = {
                '_cache_time': time.time(),
                'data': data
            }
            with open(cache_file, 'w', encoding='utf-8') as f:
                json.dump(cache_data, f, ensure_ascii=False, indent=2)
        except IOError:
            # 如果无法写入缓存，忽略错误（不影响主要功能）
            pass
    
    @staticmethod
    def get_or_compute(key: str, compute_func: Callable[[], T], expiry_seconds: Optional[int] = None) -> T:
        """获取缓存或计算值（缓存优先）
        
        Args:
            key: 缓存键
            compute_func: 计算函数（当缓存不存在或过期时调用）
            expiry_seconds: 过期时间（秒），如果为 None 则使用默认过期时间
        
        Returns:
            缓存的数据或计算后的数据
        """
        cached = CacheManager.load(key, expiry_seconds)
        if cached is not None:
            return cached
        
        value = compute_func()
        CacheManager.save(key, value)
        return value
    
    @staticmethod
    def clear(pattern: Optional[str] = None) -> None:
        """清除缓存"""
        cache_dir = CacheManager.get_cache_dir()
        if pattern:
            for cache_file in cache_dir.glob(pattern):
                cache_file.unlink()
        else:
            for cache_file in cache_dir.glob("*.json"):
                cache_file.unlink()

