using Seb.Helpers;
using UnityEngine;
using System.Collections.Generic;

namespace Seb.GPUSorting
{
    public class Scan
    {
        const int scanKernel = 0;
        const int combineKernel = 1;

        static readonly int elementsID = Shader.PropertyToID("Elements");
        static readonly int groupSumsID = Shader.PropertyToID("GroupSums");
        static readonly int itemCountID = Shader.PropertyToID("itemCount");

        readonly ComputeShader cs = ComputeHelper.LoadComputeShader("ScanTest");
        readonly Dictionary<int, ComputeBuffer> freeBuffers = new();

        public void Run(ComputeBuffer elements)
        {
            cs.GetKernelThreadGroupSizes(scanKernel, out uint threadsPerGroup, out _, out _);
            int numGroups = Mathf.CeilToInt(elements.count / 2f / threadsPerGroup);

            if (!freeBuffers.TryGetValue(numGroups, out ComputeBuffer groupSumBuffer))
            {
                groupSumBuffer = ComputeHelper.CreateStructuredBuffer<uint>(numGroups);
                freeBuffers.Add(numGroups, groupSumBuffer);
            }

            cs.SetBuffer(scanKernel, elementsID, elements);
            cs.SetBuffer(scanKernel, groupSumsID, groupSumBuffer);
            cs.SetInt(itemCountID, elements.count);

            cs.Dispatch(scanKernel, numGroups, 1, 1);

            if (numGroups > 1)
            {
                Run(groupSumBuffer);
                cs.SetBuffer(combineKernel, elementsID, elements);
                cs.SetBuffer(combineKernel, groupSumsID, groupSumBuffer);
                cs.SetInt(itemCountID, elements.count);
                cs.Dispatch(combineKernel, numGroups, 1, 1);
            }
        }

        public void Release()
        {
            foreach (var kv in freeBuffers)
                ComputeHelper.Release(kv.Value);
        }
    }
}