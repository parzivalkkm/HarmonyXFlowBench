import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { window } from '@kit.ArkUI';
import geoLocationManager from '@ohos.geoLocationManager';
import testEntry from 'libentry.so';  // 默认导入
import * as dyn from 'libdynamic.so'; // 命名空间导入
import {leak} from 'libleak.so';      // 具名导入

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onCreate');

    let info = JSON.stringify(geoLocationManager.getLastLocation());
    // 测试默认导入
    let info1 = testEntry.proxy(info);
    hilog.info(0x0000, 'testTag', 'leak LastLocation passed by cpp proxy (libentry.so) %{public}s', info1);

    // 测试具名导入
    leak(info);

    // 测试动态加载模块
    let dynamicModule: ESObject = loadNativeModule("libdynamic.so");
    dynamicModule.leak(info);

    // 测试命名空间导入
    dyn.leak(info);
  }

  onDestroy(): void {
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onDestroy');
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    // Main window is created, set main page for this ability
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onWindowStageCreate');

    windowStage.loadContent('pages/Index', (err) => {
      if (err.code) {
        hilog.error(0x0000, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err) ?? '');
        return;
      }
      hilog.info(0x0000, 'testTag', 'Succeeded in loading the content.');
    });
  }

  onWindowStageDestroy(): void {
    // Main window is destroyed, release UI related resources
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onWindowStageDestroy');
  }

  onForeground(): void {
    // Ability has brought to foreground
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onForeground');
  }

  onBackground(): void {
    // Ability has back to background
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onBackground');
  }
};
