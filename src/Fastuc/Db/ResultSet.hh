<?hh // strict
namespace Fastuc\Db;

class ResultSet implements \ArrayAccess, \Iterator, \Countable
{
	/**
	 * @var \mysqli
	 */
	private \mysqli $db;

	/**
	 * @var \mysqli_stmt
	 */
	private \mysqli_stmt $stmt;

	/**
	 * @var integer
	 */
	private int $pointer;

	/**
	 * @var array
	 */
	private array $row;

	/**
	 * @param \mysqli $db
	 * @param \mysqli_stmt $stmt
	 * @throws \Fastuc\Db\Exception If the statement couldn't be executed.
	 */
	public function __construct( \mysqli $db, \mysqli_stmt $stmt )
	{
		$this->db = $db;
		$this->stmt = $stmt;

		if( false === $stmt->execute() )
		{
			throw new Exception( $db->error );
		}

		$metadata = $stmt->result_metadata();
		$fields = $metadata->fetch_fields();
		$metadata->free_result();

		$this->pointer = 0;
		$this->row = $values = array();

		foreach( $fields as $field )
		{
			$values[] = &$this->row[ $field->name ];
		}

		$stmt->store_result();
		call_user_func_array( array( $stmt, 'bind_result' ), $values );
	}

	public function __destruct()
	{
		$this->stmt->free_result();
	}

	/**
	 * @param mixed $offset
	 * @return bool
	 */
	public function offsetExists( mixed $offset ) : bool
	{
		return ( $offset >= 0 && $offset < $this->stmt->num_rows );
	}

	/**
	 * @param mixed $offset
	 * @return array
	 */
	public function offsetGet( mixed $offset ) : array
	{
		$this->stmt->data_seek( $offset );
		$this->stmt->fetch();

		return $this->row;
	}

	/**
	 * Not used. "Read only" array iterator.
	 * @param mixed $offset
	 * @param mixed $value
	 */
	public function offsetSet( mixed $offset, mixed $value )
	{
	} 

	/**
	 * Not used. "Read only" array iterator.
	 * @param mixed $offset
	 */
	public function offsetUnset( mixed $offset )
	{
	} 

	/**
	 * @return integer
	 */
	public function count() : int
	{
		return $this->stmt->num_rows;
	}

	/**
	 * @return mixed
	 */
	public function current() : mixed
	{
		return $this->offsetGet( $this->pointer );
	}

	/**
	 * @return mixed
	 */
	public function key() : mixed
	{
		return $this->pointer;
	}

	public function next() : void
	{
		$this->pointer++;
	}

	public function rewind() : void
	{
		$this->pointer = 0;
	}

	/**
	 * @return bool
	 */
	public function valid() : bool
	{
		return $this->offsetExists( $this->pointer );
	}
}

