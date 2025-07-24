import { hilog } from '@kit.PerformanceAnalysisKit';

export class ComplexData {
  data: string;
  other: string;

  constructor() {
    this.data = '';
    this.other = '';
  }

  getData() {
    return this.data;
  }

  setData(data: string) {
    this.data = data;
  }

  getOther() {
    return this.other;
  }

  setOther(other: string) {
    this.other = other;
  }

  leakData() {
    hilog.info(0x0000, 'testTag', 'this.data = %{public}s', this.data);
  }

}