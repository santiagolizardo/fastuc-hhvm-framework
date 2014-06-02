<?hh // strict
namespace Fastuc\Html;

/**
 * Base class from where the rest the fields extend.
 */
class Field
{
	protected $id;
	protected $name;
	protected $value;
	protected $class;
	protected $required;
	protected $autofocus;

	protected $doc;

	public function __construct( $name, $value = null )
	{
		$this->name = $name;
		$this->id = $name; // @todo Don't set the ID always.

		$this->value = $value;
		$this->required = $this->autofocus = false;

		$this->doc = new \DOMDocument( '1.0', 'UTF-8' );
	}

	public function getId()
	{
		return $this->id;
	}

	/**
	 * @return This class.
	 */
	public function setId( $id )
	{
		$this->id = $id;
		return $this;
	}

	/**
	 * @return This class.
	 */
	public function setValue( $value )
	{
		$this->value = $value;
		return $this;
	}

	public function getValue()
	{
		return $this->value;
	}

	/**
	 * @return This class.
	 */
	public function setName( $name )
	{
		$this->name = $name;
		return $this;
	}

	public function getName()
	{
		return $this->name;
	}

	/**
	 * @return This class.
	 */
	public function setClass( $class )
	{
		$this->class = $class;
		return $this;
	}

	public function getClass()
	{
		return $this->class;
	}

	/**
	 * @return This class.
	 */
	public function setRequired( $required )
	{
		$this->required = $required;
		return $this;
	}

	public function isRequired()
	{
		return $this->required;
	}

	/**
	 * @return This class.
	 */
	public function setAutofocus( $autofocus )
	{
		$this->autofocus = $autofocus;
		return $this;
	}

	/**
	 * @deprecated
	 * @see hasAutofocus
	 * @return bool
	 */
	public function isAutofocus()
	{
		return $this->hasAutofocus();
	}

	/**
	 * @return bool
	 */
	public function hasAutofocus()
	{
		return $this->autofocus;
	}
}

