###作业1.用 add first 或 add last 这套新的 API 改写 Deque 的代码
源代码:
使用 LinkedList 作为底层实现时， push() 为将新的元素加入头部，peek() 为去除头元素但不删除。size()
```Java
Deque<String> deque = new LinkedList<String>();

deque.push("a");
deque.push("b");
deque.push("c");
System.out.println(deque);

String str = deque.peek();
System.out.println(str);
System.out.println(deque);

while (deque.size() > 0) {
    System.out.println(deque.pop());
}
System.out.println(deque);
```
修改后代码为：
```Java
Deque<String> deque = new LinkedList<String>();

deque.addFirst("a");
deque.addFirst("b");
deque.addFirst("c");
System.out.println(deque);

String str = deque.peekFirst();
System.out.println(str);
System.out.println(deque);

while (deque.size() > 0) {
    System.out.println(deque.removeFirst());
}
System.out.println(deque);
```

###作业2.分析 Queue 和 Priority Queue 的源码
Queue 的源码和相关的自作注释如下
```Java
package java.util;
public interface Queue<E> extends Collection<E> {
    // 定义 Queue 为 interface 接口类，继承自 Collection 类

    boolean add(E e); 
    // add 接口，用于将元素 e 插入队列中（尾部），如果插入成功则返回 True
    // 如果超出队列容量限制则抛出 IllegalStateException 异常，而不会返回 False

    boolean offer(E e);
    // offer 接口，与 add() 相似都是将元素 e 插入队列尾部，插入成功则返回 True
    // 不同的是超出队列容量限制导致插入失败时，offer() 会返回 False 而不是抛出异常
    
    E remove();
    // remove 接口，返回队列头部元素并在队列中删除此元素
    // 如果队列为空则抛出 NoSuchElementException 异常

    E poll();
    // poll 接口，返回队列头部元素并在队列中删除此元素，如果队列为空则返回 null，而不抛出异常

    E element();
    // element 接口，只对队列头部元素进行返回而不删除，如果队列为空则抛出 NoSuchElementException 异常

    E peek();
    // peek 接口，只对队列头部元素进行返回而不删除，如果队列为空则返回 null
}
```
Queue 在父类接口之上又定力了三个功能两种类别共六个接口方法：两种类别分返回 null 或抛出异常；三个功能为插入队列、返回头部、返回头部并删除头部。


Priority Queue 的源码和相关的自作注释如下
```Java
package java.util;
import java.io.Serializable;
public class PriorityQueue<E> extends AbstractQueue<E> implements Serializable
{
    // 默认容量为 11
    private static final int DEFAULT_CAPACITY = 11;

    // 队列内存中实际在使用的元素个数
    int used;
    
    // 底层存储元素的的数组实体
    E[] storage;

    // 确定优先级所用的比较器
    Comparator<? super E> comparator;

    // 几个构造函数，PriorityQueue 可以通过参数来进行构造，也可以通过传入其他 PriorityQueue 对象或者 SortedSet 对象来构造
    public PriorityQueue();
    public PriorityQueue(Collection<? extends E> c);
    public PriorityQueue(int cap);
    public PriorityQueue(int cap, Comparator<? super E> comp);
    public PriorityQueue(PriorityQueue<? extends E> c);
    public PriorityQueue(SortedSet<? extends E> c);
     
    // 清空整个对象
    // 覆写本对象内存全为 null，然后归零 used 变量
    public void clear()
    {
        Arrays.fill(storage, null);
        used = 0;
    }
    
    // 返回当前使用的比较器
    public Comparator<? super E> comparator()
    {
        return comparator;
    }
     
    // offer 接口，将元素 o 插入队列中，插入成功则返回 True
    // 首先进行异常检查，（后将 o 插入队列尾部），然后调用 bubbleUp 来按照比较器规则更新整个队列
    public boolean offer(E o)
    {
        if (o == null)
        throw new NullPointerException();
    
        int slot = findSlot(-1);
    
        storage[slot] = o;
        ++used;
        bubbleUp(slot);
    
        return true;
    }

    // peek 接口，返回队列头元素，若为空则返回 null 
    public E peek()
    {
        return used == 0 ? null : storage[0];
    }

    // poll 接口，返回队列头元素并删除头元素，若为空则返回 null
    public E poll()
    {
        if (used == 0)
            return null;
        E result = storage[0];
        remove(0);
        return result;
    }

    // remove 的一个函数重载版本，如果传入的是一个 Object o，则遍历整个队列找到和 o 相等的元素从队列中删除，此处删除具体的元素使用的是另一个 remove 重载版本，在后面会有代码
    // 成功删除则返回 True, 删除失败则返回 False.
    public boolean remove(Object o)
    {
        if (o != null)
        {
            for (int i = 0; i < storage.length; ++i)
            {
                if (o.equals(storage[i]))
                {
                    remove(i);
                    return true;
                }
            }
        }
        return false;
    }

    // size 接口，返回当前队列中的元素个数
    public int size()
    {
        return used;
    }

    // 将另一个 Collection 类对象 c 的所有元素添加到本队列中
    // 首先进行判断避免自我复制，后返回添加结果
    public boolean addAll(Collection<? extends E> c)
    {
        if (c == this)
            throw new IllegalArgumentException();

        int newSlot = -1;
        int save = used;
        for (E val : c)
        {
            if (val == null)
                throw new NullPointerException();
            newSlot = findSlot(newSlot);
            storage[newSlot] = val;
            ++used;
            bubbleUp(newSlot);
        }

        return save != used;
    }

    // findSlot 方法返回当前空闲位置的第一个下标，用于在队列中放置新元素
    // 注意，如果当前空间已满会进行 resize() 扩容，所以这个方法总会返回一个可以放置新元素的位置
    int findSlot(int start)
    {
        int slot;
        if (used == storage.length)
        {
            resize();
            slot = used;
        }
        else
        {
            for (slot = start + 1; slot < storage.length; ++slot)
            {
                if (storage[slot] == null)
                    break;
            }
            // We'll always find a slot.
        }
        return slot;
    }

    // 移除一个元素所使用的实际操作版本，传入的是元素在队列中的下标值
    // 并不是简单的移除位于 index 处的元素，还需要进行整个优先队列的维护
    // 维护过程为不断将子结点填补到被移除的结点处，直到当前子树结束的位置
    void remove(int index)
    {
        // 会一直迭代到队列尾部
        while (storage[index] != null)
        {
            int child = 2 * index + 1;

            // 如果被移除的节点没有子节点，即到达了子树的尾部，则结束
            if (child >= storage.length)
            {
                storage[index] = null;
                break;
            }

            // 如果当前节点只有一个子节点，则将此节点移到此处
            // 如果有两个子节点，则将优先级高的子节点移到此处(视comparator而定，默认是greater，更小的值优先级更高)
            if (child + 1 >= storage.length || storage[child + 1] == null)
            {
                // Nothing.
            }
            else if (storage[child] == null
                    || (Collections.compare(storage[child], storage[child + 1], comparator) > 0))
                ++child;
            storage[index] = storage[child];
            index = child;
        }
        --used;
    }

    // 在尾部插入元素后，就会调用此 bubbleUp 方法来将优先队列进行调整，使新元素到达其正确的位置
    void bubbleUp(int index)
    {
        // The element at INDEX was inserted into a blank spot.  Now move
        // it up the tree to its natural resting place.
        while (index > 0)
        {
            // 寻找当前元素的父节点元素
            int parent = (index - 1) / 2;
            if (Collections.compare(storage[parent], storage[index], comparator) <= 0)
            {
                // 如果父节点比此节点优先级高，则位置无需再调整，已达到优先队列的正确形态，便退出
                break;
            }

            // 交换当前节点与父节点的值，使当前元素优先级变高
            E temp = storage[index];
            storage[index] = storage[parent];
            storage[parent] = temp;

            // 更新 index 的值，使其继续与新的父节点进行比较
            index = parent;
        }
    }

    // resize() 方法对本队列空间进行扩容，扩充为原来大小的两倍，也就是指数级增长
    // 后会将原有数据拷贝至新内存中
    void resize()
    {
        E[] new_data = (E[]) new Object[2 * storage.length];
        System.arraycopy(storage, 0, new_data, 0, storage.length);
        storage = new_data;
    }
}
```
PriorityQueue 使用数组作为其容器，用数组按层次顺序存储二叉树，当前第i个元素（从0开始）的左子节点元素的下标为 2×i+1，右子节点元素的下标为 2×i+2，也可得其父节点元素的下标为 (i-1)/2，。
PriorityQueue 采用的扩容机制为加倍增长，即每次新的容器大小都变为原来大小的二倍。
PriorityQueue 的核心是对其优先级的维护，体现为每次添加新元素和删除原有元素后需要按照优先级对当前数列进行时间复杂度为 O(logn) 的迭代维护。
PriorityQueue 默认的 comparator 为 greater，即为小顶堆。
PriorityQueue 提供的对外接口有 clear,offer,peek,poll,remove,size,resize等，其时间复杂度分别为：
    1. offer: O(logn)
    2. peek: O(1)
    3. poll: O(logn)
    4. remove: 如果是删除指定元素（传入参数为元素），则首先进行遍历找到下标，这一步为 O(n)，之后再对其进行删除和队列维护，这一步是 O(logn)，故整体为 O(n)；如果是删除指定下标的元素，那就是 O(logn)
    5. size: O(1)